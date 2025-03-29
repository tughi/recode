#include "Checker.h"
#include "File.h"
#include "Generator.h"
#include "Parser.h"

void help_recode() {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "   \033[1mrecode\033[0m [options] <command> <file>\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "   \033[1m--output-dir\033[0m <dir>   set output directory\n");
    fprintf(stderr, "   \033[1m--project-dir\033[0m <dir>  set project directory\n");
    fprintf(stderr, "Commands:\n");
    fprintf(stderr, "   \033[1mapp\033[0m                  compile app\n");
    fprintf(stderr, "   \033[1mlib\033[0m                  compile lib\n");
}

int32_t main(int32_t argc, char **argv) {
    File__init();

    if (argc == 1) {
        help_recode();
        return 1;
    }

    int arg = 1;
    String *output_dir = NULL;
    String *project_dir = NULL;
    while (argv[arg][0] == '-') {
        char *option = argv[arg];
        if (strcmp(option, "--output-dir") == 0) {
            if (output_dir != NULL) {
                fprintf(stderr, "Duplicate --output-dir option\n");
                help_recode();
                return 1;
            }
            arg++;
            if (arg >= argc) {
                fprintf(stderr, "Missing argument for --output-dir\n");
                help_recode();
                return 1;
            }
            output_dir = String__create_from(argv[arg]);
            arg++;
        } else if (strcmp(option, "--project-dir") == 0) {
            if (project_dir != NULL) {
                fprintf(stderr, "Duplicate --project-dir option\n");
                help_recode();
                return 1;
            }
            arg++;
            if (arg >= argc) {
                fprintf(stderr, "Missing argument for --project-dir\n");
                help_recode();
                return 1;
            }
            project_dir = String__create_from(argv[arg]);
            arg++;
        } else {
            fprintf(stderr, "Unknown option: %s\n", option);
            help_recode();
            return 1;
        }
    }

    char *command = argv[arg];
    bool generate_main;
    if (strcmp(command, "app") == 0) {
        generate_main = true;
    } else if (strcmp(command, "lib") == 0) {
        generate_main = false;
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        help_recode();
        return 1;
    }

    arg++;
    if (arg >= argc) {
        fprintf(stderr, "Missing file\n");
        help_recode();
        return 1;
    }
    String *file_path = String__create_from(argv[arg]);
    if (file_path->length <= 5 || !String__ends_with_cstring(file_path, ".code")) {
        fprintf(stderr, "Expected a .code file\n");
        help_recode();
        return 1;
    }

    arg++;
    if (arg < argc) {
        fprintf(stderr, "Too many arguments\n");
        help_recode();
        return 1;
    }

    if (project_dir == NULL) {
        project_dir = String__create_from("./");
    } else if (!String__ends_with_cstring(project_dir, "/")) {
        String__append_char(project_dir, '/');
    }
    Parsed_Source *parsed_source = parse(project_dir, file_path);

    Checked_Source *checked_source = check(parsed_source);

    if (output_dir == NULL) {
        output_dir = String__create_from(".generated");
    }
    generate(checked_source, output_dir, generate_main);

    return 0;
}
