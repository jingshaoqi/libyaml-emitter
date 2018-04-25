#include <yaml.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

// void print_escaped(yaml_char_t* str, size_t length);
bool get_line(FILE *input, char *line);
char *get_anchor(char sigil, char *line, char *anchor);
char *get_tag(char *line, char *tag);
void get_value(char *line, char *value, yaml_scalar_style_t *style);

static int generate_simple_map_yaml();
static int generate_sequence_yaml();
static int generate_yaml(int argc, char *argv[]);

/* generate_simple_map_yaml function will generate  simple_map.yaml

invoice: 34843
date: 2001-01-23

*/
static int generate_simple_map_yaml()
{
    FILE *out_file = NULL;
    yaml_emitter_t emitter;
    yaml_event_t event;

    int canonical = 0;
    int unicode = 0;
    int ok = 0;

    char* p_anchor = NULL;
    char* p_tag=NULL;
    yaml_scalar_style_t style;
    const char* value = NULL;
    int implicit=1;

    out_file = fopen("simple_map.yaml", "wb");
    if(!out_file){
        fprintf(stderr, "fopen fail:%s\n", strerror(errno));
        return -1;
    }

    if (!yaml_emitter_initialize(&emitter)) {
        fprintf(stderr, "Could not initalize the emitter object\n");
        return 1;
    }

    yaml_emitter_set_output_file(&emitter, out_file);
    yaml_emitter_set_canonical(&emitter, canonical);
    yaml_emitter_set_unicode(&emitter, unicode);

    /* stream start event initialize */
    ok = yaml_stream_start_event_initialize(&event,YAML_UTF8_ENCODING);
    yaml_emitter_emit(&emitter, &event);

    ok = yaml_document_start_event_initialize(&event,NULL,NULL,NULL,implicit);
    yaml_emitter_emit(&emitter, &event);


    /* mapping start event initialize */
    p_anchor = NULL;
    p_tag=NULL;
    ok = yaml_mapping_start_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,0,0);
    yaml_emitter_emit(&emitter, &event);

    /*  invoice: 34843 */
    p_anchor = NULL;
    p_tag=NULL;
    style = YAML_PLAIN_SCALAR_STYLE;
    value = "invoice";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);
    value = "34843";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);

    /* date: 2001-01-23 */
    value = "date";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);
    value = "2001-01-23";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);


    /* mapping end event initialize */
    ok = yaml_mapping_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);


    ok = yaml_document_end_event_initialize(&event,implicit);
    yaml_emitter_emit(&emitter, &event);

    /* stream  end event initialize */
    ok = yaml_stream_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);

    yaml_emitter_delete(&emitter);
    fclose(out_file);
    out_file = NULL;
    return 0;
}

/* generate_sequence_yaml function will generate  sequence.yaml

product:
- sku: BL394D
  quantity: 4
- sku: BL4438H
  quantity: 1

*/
static int generate_sequence_yaml()
{
    FILE *out_file = NULL;
    yaml_emitter_t emitter;
    yaml_event_t event;

    int canonical = 0;
    int unicode = 0;
    int ok = 0;

    char* p_anchor = NULL;
    char* p_tag=NULL;
    yaml_scalar_style_t style;
    const char* value = NULL;
    int implicit=1;

    out_file = fopen("sequence.yaml", "wb");
    if(!out_file){
        fprintf(stderr, "fopen fail:%s\n", strerror(errno));
        return -1;
    }

    if (!yaml_emitter_initialize(&emitter)) {
        fprintf(stderr, "Could not initalize the emitter object\n");
        return 1;
    }

    yaml_emitter_set_output_file(&emitter, out_file);
    yaml_emitter_set_canonical(&emitter, canonical);
    yaml_emitter_set_unicode(&emitter, unicode);

    /* stream start event initialize */
    ok = yaml_stream_start_event_initialize(&event,YAML_UTF8_ENCODING);
    yaml_emitter_emit(&emitter, &event);

    ok = yaml_document_start_event_initialize(&event,NULL,NULL,NULL,implicit);
    yaml_emitter_emit(&emitter, &event);


    /* mapping start event initialize */
    ok = yaml_mapping_start_event_initialize(&event,NULL,NULL,0,0);
    yaml_emitter_emit(&emitter, &event);

    /*  product:  */
    style = YAML_PLAIN_SCALAR_STYLE;
    value = "product";
    ok = yaml_scalar_event_initialize(&event,NULL,NULL,(yaml_char_t *)value,-1,1, 1,YAML_PLAIN_SCALAR_STYLE);
    yaml_emitter_emit(&emitter, &event);

    /* sequence start event initialize */
    ok = yaml_sequence_start_event_initialize(&event,NULL,NULL,1,YAML_BLOCK_SEQUENCE_STYLE);
    yaml_emitter_emit(&emitter, &event);

    /* mapping start event initialize */
    ok = yaml_mapping_start_event_initialize(&event,NULL,NULL,0,0);
    yaml_emitter_emit(&emitter, &event);

    /* - sku: BL394D */
    value = "sku";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);
    value = "BL394D";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);

    /* quantity: 4 */
    value = "quantity";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);
    value = "4";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);

    /* mapping end event initialize */
    ok = yaml_mapping_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);



    /* mapping start event initialize */
    ok = yaml_mapping_start_event_initialize(&event,NULL,NULL,0,0);
    yaml_emitter_emit(&emitter, &event);

    /* - sku: BL4438H */
    value = "sku";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);
    value = "BL4438H";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);

    /* quantity: 1 */
    value = "quantity";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);
    value = "1";
    ok = yaml_scalar_event_initialize(&event,(yaml_char_t *)p_anchor,(yaml_char_t *)p_tag,(yaml_char_t *)value,-1,1, 1,style);
    yaml_emitter_emit(&emitter, &event);

    /* mapping end event initialize */
    ok = yaml_mapping_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);


    /* sequence end event initialize */
    ok = yaml_sequence_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);





    /* mapping end event initialize */
    ok = yaml_mapping_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);


    ok = yaml_document_end_event_initialize(&event,implicit);
    yaml_emitter_emit(&emitter, &event);

    /* stream  end event initialize */
    ok = yaml_stream_end_event_initialize(&event);
    yaml_emitter_emit(&emitter, &event);

    yaml_emitter_delete(&emitter);
    fclose(out_file);
    out_file = NULL;
    return 0;
}

static int generate_yaml(int argc, char *argv[])
{
    FILE *input;
    yaml_emitter_t emitter;
    yaml_event_t event;

    int canonical = 0;
    int unicode = 0;
    char line[1024];

    if (argc == 1)
        input = stdin;
    else if (argc == 2){
        input = fopen(argv[1], "rb");
        fprintf(stdout, "input file:%s\n", argv[1]);
    }  else {
        fprintf(stderr, "Usage: libyaml-emitter [<input-file>]\n");
        return 1;
    }
    assert(input);

    if (!yaml_emitter_initialize(&emitter)) {
        fprintf(stderr, "Could not initalize the emitter object\n");
        return 1;
    }
    yaml_emitter_set_output_file(&emitter, stdout);
    yaml_emitter_set_canonical(&emitter, canonical);
    yaml_emitter_set_unicode(&emitter, unicode);

    while (get_line(input, line)) {
        int ok;
        char anchor[256];
        char tag[256];
        int implicit;
        fprintf(stdout, "line:%s\n", line);
        fflush(stdout);

        if (strncmp(line, "+STR", 4) == 0) {
            ok = yaml_stream_start_event_initialize(
                        &event,
                        YAML_UTF8_ENCODING
                        );
        }
        else if (strncmp(line, "-STR", 4) == 0) {
            ok = yaml_stream_end_event_initialize(&event);
        }
        else if (strncmp(line, "+DOC", 4) == 0) {
            implicit = strncmp(line, "+DOC ---", 8) != 0;
            ok = yaml_document_start_event_initialize(
                        &event,
                        NULL,
                        NULL,
                        NULL,
                        implicit
                        );
        }
        else if (strncmp(line, "-DOC", 4) == 0) {
            implicit = strncmp(line, "-DOC ...", 8) != 0;
            ok = yaml_document_end_event_initialize(
                        &event,
                        implicit
                        );
        }
        else if (strncmp(line, "+MAP", 4) == 0) {
            char* p_anchor = get_anchor('&', line, anchor);
            char* p_tag=get_tag(line, tag);
            ok = yaml_mapping_start_event_initialize(
                        &event,
                        (yaml_char_t *)p_anchor,
                        (yaml_char_t *)p_tag,
                        0,
                        0
                        );
        }
        else if (strncmp(line, "-MAP", 4) == 0) {
            ok = yaml_mapping_end_event_initialize(&event);
        }
        else if (strncmp(line, "+SEQ", 4) == 0) {
            char* p_anchor =get_anchor('&', line, anchor);
            char* p_tag=get_tag(line, tag);
            ok = yaml_sequence_start_event_initialize(
                        &event,
                        (yaml_char_t *)p_anchor,
                        (yaml_char_t *)p_tag,
                        1,
                        YAML_BLOCK_SEQUENCE_STYLE
                        );
        }
        else if (strncmp(line, "-SEQ", 4) == 0) {
            ok = yaml_sequence_end_event_initialize(&event);
        }
        else if (strncmp(line, "=VAL", 4) == 0) {
            char value[1024];
            yaml_scalar_style_t style;

            get_value(line, value, &style);
            char* p_anchor =get_anchor('&', line, anchor);
            char* p_tag=get_tag(line, tag);
            ok = yaml_scalar_event_initialize(
                        &event,
                        (yaml_char_t *)p_anchor,
                        (yaml_char_t *)p_tag,
                        (yaml_char_t *)value,
                        -1,
                        1,
                        1,
                        style
                        );
        }
        else if (strncmp(line, "=ALI", 4) == 0) {
            char* p_anchor =get_anchor('*', line, anchor);
            ok = yaml_alias_event_initialize(
                        &event,
                        (yaml_char_t *)p_anchor
                        );
        }
        else {
            fprintf(stderr, "Unknown event: '%s'\n", line);
            fflush(stdout);
            return 1;
        }

        if (!ok)
            goto event_error;
        if (!yaml_emitter_emit(&emitter, &event))
            goto emitter_error;
    }

    assert(!fclose(input));
    yaml_emitter_delete(&emitter);
    fflush(stdout);

    return 0;

emitter_error:
    switch (emitter.error) {
    case YAML_MEMORY_ERROR:
        fprintf(stderr, "Memory error: Not enough memory for emitting\n");
        break;
    case YAML_WRITER_ERROR:
        fprintf(stderr, "Writer error: %s\n", emitter.problem);
        break;
    case YAML_EMITTER_ERROR:
        fprintf(stderr, "Emitter error: %s\n", emitter.problem);
        break;
    default:
        /* Couldn't happen. */
        fprintf(stderr, "Internal error\n");
        break;
    }
    yaml_emitter_delete(&emitter);
    return 1;

event_error:
    fprintf(stderr, "Memory error: Not enough memory for creating an event\n");
    yaml_emitter_delete(&emitter);
    return 1;
}

int main(int argc, char *argv[])
{
    generate_simple_map_yaml();
    generate_sequence_yaml();
 //   generate_yaml(argc, argv);
}

bool get_line(FILE *input, char *line) {
    char *newline;

    if (!fgets(line, 1024 - 1, input))
        return false;

    if ((newline = strchr(line, '\n')) == NULL) {
        fprintf(stderr, "Line too long: '%s'", line);
        abort();
    }
    *newline = '\0';

    return true;
}

char *get_anchor(char sigil, char *line, char *anchor) {
    char *start;
    char *end;
    if ((start = strchr(line, sigil)) == NULL)
        return NULL;
    start++;
    if ((end = strchr(start, ' ')) == NULL)
        end = line + strlen(line);
    memcpy(anchor, start, end - start);
    anchor[end - start] = '\0';
    return anchor;
}

char *get_tag(char *line, char *tag) {
    char *start;
    char *end;
    if ((start = strchr(line, '<')) == NULL)
        return NULL;
    if ((end = strchr(line, '>')) == NULL)
        return NULL;
    memcpy(tag, start + 1, end - start - 1);
    tag[end - start -1] = '\0';
    return tag;
}

void get_value(char *line, char *value, yaml_scalar_style_t *style) {
    int i = 0;
    char *c;
    char *start = NULL;
    char *end = line + strlen(line);

    for (c = line + 4; c < end; c++) {
        if (*c == ' ') {
            start = c + 1;
            if (*start == ':')
                *style = YAML_PLAIN_SCALAR_STYLE;
            else if (*start == '\'')
                *style = YAML_SINGLE_QUOTED_SCALAR_STYLE;
            else if (*start == '"')
                *style = YAML_DOUBLE_QUOTED_SCALAR_STYLE;
            else if (*start == '|')
                *style = YAML_LITERAL_SCALAR_STYLE;
            else if (*start == '>')
                *style = YAML_FOLDED_SCALAR_STYLE;
            else {
                start = NULL;
                continue;
            }
            start++;
            break;
        }
    }
    if (!start)
        abort();

    for (c = start; c < end; c++) {
        if (*c == '\\') {
            if (*++c == '\\')
                value[i++] = '\\';
            else if (*c == '0')
                value[i++] = '\0';
            else if (*c == 'b')
                value[i++] = '\b';
            else if (*c == 'n')
                value[i++] = '\n';
            else if (*c == 'r')
                value[i++] = '\r';
            else if (*c == 't')
                value[i++] = '\t';
            else
                abort();
        }
        else
            value[i++] = *c;
    }
    value[i] = '\0';
}
