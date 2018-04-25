#include <yaml.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

typedef enum insert_status_e{
    INSERT_STATUS_START = 0,
    INSERT_STATUS_MIDDLE,
    INSERT_STATUS_END,
}insert_status_t;

typedef struct unit_e{
    unsigned char* data;
    int length;
}unit_t;

typedef struct map_item_e{
    unit_t* key;
    unit_t* value;
}map_item_t;

#define CHECK_RETURN(ret) \
    do { \
    if(ret != 1)    \
    goto fail; \
    }while(0)


static int map_insert_one(yaml_emitter_t* emitter, yaml_event_t* event,insert_status_t status, map_item_t* item);
static int sequence_insert_one(yaml_emitter_t* emitter,yaml_event_t* event, insert_status_t status, unit_t* unit);


static yaml_emitter_t* emitter_create(FILE* out_file, yaml_event_t** pp_event);
static int emitter_free(yaml_emitter_t** pp_emitter, yaml_event_t** pp_event);


static int map_insert_one(yaml_emitter_t* emitter,yaml_event_t* event, insert_status_t status, map_item_t* item)
{
    int ret = 0;
    switch (status) {
    case INSERT_STATUS_START:
        ret = yaml_mapping_start_event_initialize(event,NULL, NULL,0,0);
        break;
    case INSERT_STATUS_MIDDLE:
        ret = yaml_scalar_event_initialize(event,NULL, NULL,
                                           (yaml_char_t *)item->key->data,item->key->length,1, 1,YAML_PLAIN_SCALAR_STYLE);
        if(!item->value)
            break;

        if(ret != 1){  return ret; }
        ret = yaml_emitter_emit(emitter, event);
        if(ret != 1){  return ret; }
        ret = yaml_scalar_event_initialize(event,NULL, NULL,
                                           (yaml_char_t *)item->value->data,item->value->length,1, 1,YAML_PLAIN_SCALAR_STYLE);
        break;
    case INSERT_STATUS_END:
        ret = yaml_mapping_end_event_initialize(event);
        break;
    default:
        ret = 0;//error
        break;
    }

    if(ret != 1)
        return ret;
    ret = yaml_emitter_emit(emitter, event);
    return ret;
}
static int sequence_insert_one(yaml_emitter_t* emitter,yaml_event_t* event, insert_status_t status, unit_t* unit)
{
    int ret = 0;
    switch (status) {
    case INSERT_STATUS_START:
        ret = yaml_sequence_start_event_initialize(event,NULL,NULL,1,YAML_BLOCK_SEQUENCE_STYLE);
        break;
    case INSERT_STATUS_MIDDLE:
        ret = yaml_scalar_event_initialize(event,NULL, NULL,
                                           (yaml_char_t *)unit->data,unit->length,1, 1,YAML_PLAIN_SCALAR_STYLE);

        break;
    case INSERT_STATUS_END:
        ret = yaml_sequence_end_event_initialize(event);
        break;
    default:
        ret = 0;//error
        break;
    }

    if(ret != 1)
        return ret;
    ret = yaml_emitter_emit(emitter, event);
    return ret;
}

static yaml_emitter_t* emitter_create(FILE* out_file, yaml_event_t** pp_event)
{
    int ret = 0;
    int implicit = 1;
    yaml_event_t* event = (yaml_event_t*)malloc(sizeof(yaml_event_t));
    if(!event){
        return NULL;
    }
    yaml_emitter_t* emitter = (yaml_emitter_t*)malloc(sizeof(yaml_emitter_t));
    if(!emitter){
        goto fail;
    }

    if (!yaml_emitter_initialize(emitter)) {
        fprintf(stderr, "Could not initalize the emitter object\n");
        goto fail;
    }

    yaml_emitter_set_output_file(emitter, out_file);
    yaml_emitter_set_canonical(emitter, 0);
    yaml_emitter_set_unicode(emitter, 0);

    /* stream start event initialize */
    ret = yaml_stream_start_event_initialize(event,YAML_UTF8_ENCODING);
    CHECK_RETURN(ret);
    ret = yaml_emitter_emit(emitter, event);
    CHECK_RETURN(ret);

    ret = yaml_document_start_event_initialize(event,NULL,NULL,NULL,implicit);
    CHECK_RETURN(ret);
    ret = yaml_emitter_emit(emitter, event);
    CHECK_RETURN(ret);
    if(pp_event){
        *pp_event = event;
    }
    return emitter;
fail:
    free(event);
    event = NULL;
    return NULL;
}
static int emitter_free(yaml_emitter_t** pp_emitter, yaml_event_t** pp_event)
{
    yaml_emitter_t* emitter = *pp_emitter;
    yaml_event_t* event = *pp_event;
    int ret = yaml_document_end_event_initialize(event,1);
    CHECK_RETURN(ret);
    yaml_emitter_emit(emitter, event);
    CHECK_RETURN(ret);

    /* stream  end event initialize */
    ret = yaml_stream_end_event_initialize(event);
    CHECK_RETURN(ret);
    yaml_emitter_emit(emitter, event);
    CHECK_RETURN(ret);

    yaml_emitter_delete(emitter);
    *pp_emitter = NULL;
    *pp_event = NULL;
    return 1;
fail:
    return 0;//error
}

/*  test.yaml

product:
- sku: BL394D
  quantity: 4
- sku: BL4438H
  quantity: 1

*/


int main(int argc, char *argv[])
{
    FILE* out_file = fopen("test.yaml", "wb");
    if(!out_file){
        return -1;
    }

    unit_t unit;
    map_item_t mi;
    unit_t key;
    unit_t value;
    mi.key = &key;
    mi.value = &value;

    yaml_event_t* event = NULL;
    yaml_emitter_t* emitter =  emitter_create(out_file, &event);
    if(!emitter){
        return -1;
    }

    map_insert_one(emitter, event, INSERT_STATUS_START, NULL);

    key.data = "product";
    key.length = strlen(key.data);
    mi.key = &key;
    mi.value = NULL;
    map_insert_one(emitter, event, INSERT_STATUS_MIDDLE, &mi);

    sequence_insert_one(emitter, event, INSERT_STATUS_START, NULL);

    map_insert_one(emitter, event, INSERT_STATUS_START, NULL);

    key.data = "sku";
    key.length = strlen(key.data);
    value.data = "BL394D";
    value.length = strlen(value.data);
    mi.key = &key;
    mi.value = &value;
    map_insert_one(emitter, event, INSERT_STATUS_MIDDLE, &mi);

    key.data = "quantity";
    key.length = strlen(key.data);
    value.data = "4";
    value.length = strlen(value.data);
    mi.key = &key;
    mi.value = &value;
    map_insert_one(emitter, event, INSERT_STATUS_MIDDLE, &mi);

    map_insert_one(emitter, event, INSERT_STATUS_END, NULL);


    map_insert_one(emitter, event, INSERT_STATUS_START, NULL);

    key.data = "sku";
    key.length = strlen(key.data);
    value.data = "BL4438H";
    value.length = strlen(value.data);
    mi.key = &key;
    mi.value = &value;
    map_insert_one(emitter, event, INSERT_STATUS_MIDDLE, &mi);

    key.data = "quantity";
    key.length = strlen(key.data);
    value.data = "1";
    value.length = strlen(value.data);
    mi.key = &key;
    mi.value = &value;
    map_insert_one(emitter, event, INSERT_STATUS_MIDDLE, &mi);

    map_insert_one(emitter, event, INSERT_STATUS_END, NULL);

     sequence_insert_one(emitter, event, INSERT_STATUS_END, NULL);
     map_insert_one(emitter, event, INSERT_STATUS_END, NULL);

     emitter_free(&emitter, &event);
     fclose(out_file);
     out_file = NULL;

    return 0;
}
