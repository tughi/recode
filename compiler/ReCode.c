#include "Checker.h"
#include "File.h"
#include "Generator.h"
#include "Lowerer.h"
#include "Parser.h"

void help_recode(char *executable) {
    fprintf(stderr, "Usage: \033[1m%s\033[0m [OPTIONS] <SOURCE-DIR> [PACKAGE]\n", executable);
    fprintf(stderr, "\n");
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, "  \033[1m<SOURCE-DIR>\033[0m                Path to the source directory\n");
    fprintf(stderr, "  \033[1m[PACKAGE]\033[0m                   The specific package name to build (optional)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  \033[1m-o\033[0m, \033[1m--output\033[0m <DIR>          Output directory [default: ./build]\n");
    fprintf(stderr, "  \033[1m-n\033[0m, \033[1m--name\033[0m <NAME>           Name of the resulting executable [default: PACKAGE or app]\n");
    fprintf(stderr, "  \033[1m-h\033[0m, \033[1m--help\033[0m                  Show this help message\n");
}

int32_t main(int32_t argc, char **argv) {
    File__init();

    if (argc == 1) {
        help_recode(argv[0]);
        return 1;
    }

    int arg = 1;
    String *output_dir = NULL;
    String *binary_name = NULL;
    while (arg < argc && argv[arg][0] == '-') {
        char *option = argv[arg];
        if (strcmp(option, "-h") == 0 || strcmp(option, "--help") == 0) {
            help_recode(argv[0]);
            return 0;
        } else if (strcmp(option, "-o") == 0 || strcmp(option, "--output") == 0) {
            arg++;
            if (arg >= argc) {
                fprintf(stderr, "\nExpected <DIR> after %s\n", option);
                return 1;
            }
            output_dir = String__create_from(argv[arg]);
            arg++;
        } else if (strcmp(option, "-n") == 0 || strcmp(option, "--name") == 0) {
            arg++;
            if (arg >= argc) {
                fprintf(stderr, "\nExpected <NAME> after %s\n", option);
                return 1;
            }
            binary_name = String__create_from(argv[arg]);
            arg++;
        } else {
            fprintf(stderr, "\nUnknown option: %s\n", option);
            return 1;
        }
    }

    if (arg >= argc) {
        fprintf(stderr, "\nMissing <SOURCE-DIR>\n");
        return 1;
    }
    String *source_dir = String__create_from(argv[arg]);
    if (!Path__is_directory(source_dir)) {
        fprintf(stderr, "\nNot a directory: %s\n", source_dir->data);
        return 1;
    }
    arg++;

    String *package_name = NULL;
    if (arg < argc) {
        package_name = String__create_from(argv[arg]);
        arg++;
    }

    if (arg < argc) {
        fprintf(stderr, "\nToo many arguments\n");
        return 1;
    }

    if (binary_name == NULL) {
        if (package_name != NULL) {
            binary_name = String__create_from(package_name->data);
        } else {
            binary_name = String__create_from("app");
        }
    }

    if (output_dir == NULL) {
        output_dir = String__create_from("./build");
    }
    if (!Path__is_directory(output_dir)) {
        fprintf(stderr, "\nNot a directory: %s\n", output_dir->data);
        return 1;
    }

    Parsed_Package *main_package = parse_package(source_dir, package_name, binary_name);

    Parsed_Package *builtin_package = parse_package(String__create_from("code"), String__create_from("builtin"), NULL);

    Checked_Source *checked_source = check(builtin_package, main_package);

    checked_source = lower(checked_source);

    generate(checked_source, output_dir, true);

    return 0;
}
