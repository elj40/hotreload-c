#include <stdio.h>
#include <dlfcn.h>

typedef void* module_main_ptr(void * state);
int main()
{
    void * state = NULL;

    while (1)
    {
        void * module = dlopen("./main.so", RTLD_NOW);

        if (!module) printf("Could not load module: [%s]\n", dlerror());
        else printf("Loaded module\n");

        module_main_ptr * module_main = dlsym(module, "module_main");

        if (!module_main) printf("Could not load module_main\n");
        else printf("Loaded module_main\n");

        state = module_main(state);

        dlclose(module);

        if (!state) break;
    };

    return 0;
};
