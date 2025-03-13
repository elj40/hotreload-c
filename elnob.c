#define ELNOB_IMPLEMENTATION
#include "elnob.h"
#include <sys/stat.h>

#define ELNOB_OUTFILE "elnob.out"

int main()
{
    struct stat code_stat;
    struct stat libh_stat;
    struct stat exec_stat;

    stat(__FILE__, &code_stat);
    stat("elnob.h", &libh_stat);
    stat(ELNOB_OUTFILE, &exec_stat);

    if (code_stat.st_mtime > exec_stat.st_mtime || libh_stat.st_mtime > exec_stat.st_mtime)
    {
        printf("==================== ELNOB RECOMPILING ========================\n");
        const char * recompile[] = {"gcc", "-o", ELNOB_OUTFILE, __FILE__, NULL};
        if (!run_command_sync(ELNOB_ARRAY_SIZE(recompile), recompile)) return 1;

        const char * rerun[] = { "./"ELNOB_OUTFILE, NULL };
        return run_command_sync(ELNOB_ARRAY_SIZE(rerun), rerun);
    }
   
    printf("==================== ELNOB RUNNING ============================\n");
    const char * cmp_main[] = {"gcc", "-shared", "-o", "main.so", "main.c", NULL};
    if (!run_command_sync(ELNOB_ARRAY_SIZE(cmp_main), cmp_main)) return 1;
    const char * cmp_reload[] = {"gcc", "-o", "reload.out", "reload.c", NULL};
    if (!run_command_sync(ELNOB_ARRAY_SIZE(cmp_reload), cmp_reload)) return 1;

    // const char * run[] = {"./reload.out", NULL};
    // if (!run_command_sync(ELNOB_ARRAY_SIZE(run), run)) return 1;

    return 0;
};
