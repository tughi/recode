#include "Checker.h"
#include "File.h"
#include "Generator.h"
#include "Parser.h"

void help_recode() {
    fprintf(stderr, "Usage: \033[1mrecode\033[0m [OPTIONS] CODE\n");
    fprintf(stderr, "  ReCode: The Code compiler\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  \033[1m-h\033[0m, \033[1m--help\033[0m                  Show this help message\n");
    fprintf(stderr, "  \033[1m-o\033[0m, \033[1m--output-dir\033[0m PATH       Directory for generated files\n");
    fprintf(stderr, "  \033[1m-p\033[0m, \033[1m--project-name\033[0m PATH     Project name\n");
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
    String *project_name = NULL;
    while (argv[arg][0] == '-') {
        char *option = argv[arg];
        if (strcmp(option, "-h") == 0 || strcmp(option, "--help") == 0) {
            help_recode();
            return 0;
        } else if (strcmp(option, "-o") == 0 || strcmp(option, "--output-dir") == 0) {
            if (output_dir != NULL) {
                help_recode();
                fprintf(stderr, "\nUnexpected extra option: %s\n", option);
                return 1;
            }
            arg++;
            if (arg >= argc) {
                help_recode();
                fprintf(stderr, "\nExpected <dir> after %s\n", option);
                return 1;
            }
            output_dir = String__create_from(argv[arg]);
            arg++;
        } else if (strcmp(option, "-p") == 0 || strcmp(option, "--project-name") == 0) {
            if (project_name != NULL) {
                help_recode();
                fprintf(stderr, "\nUnexpected extra option: %s\n", option);
                return 1;
            }
            arg++;
            if (arg >= argc) {
                help_recode();
                fprintf(stderr, "\nExpected <name> after %s\n", option);
                return 1;
            }
            project_name = String__create_from(argv[arg]);
            arg++;
        } else {
            help_recode();
            fprintf(stderr, "\nUnknown option: %s\n", option);
            return 1;
        }
    }

    if (arg >= argc) {
        help_recode();
        fprintf(stderr, "\nMissing file\n");
        return 1;
    }
    String *path = String__create_from(argv[arg]);
    if (!Path__exists(path)) {
        help_recode();
        fprintf(stderr, "\nPath does not exist: %s\n", path->data);
        return 1;
    }
    if (Path__is_directory(path)) {
        project_dir = path;
    } else if (path->length <= 5 || !String__ends_with_cstring(path, ".code")) {
        help_recode();
        fprintf(stderr, "\nExpected a .code file\n");
        return 1;
    } else {
        project_dir = Path__get_parent(path);
    }

    arg++;
    if (arg < argc) {
        help_recode();
        fprintf(stderr, "\nToo many arguments\n");
        return 1;
    }

    if (project_name == NULL) {
        project_name = String__create_from("main");
    }

    Parsed_Package *main_package = parse_package(project_dir, NULL, project_name);

    Parsed_Package *builtin_package = parse_package(String__create_from("code"), String__create_from("builtin"), String__create_from("builtin"));

    Checked_Source *checked_source = check(builtin_package, main_package);

    if (output_dir == NULL) {
        output_dir = String__create_from(".generated");
    }
    generate(checked_source, output_dir, true);

    return 0;
}
