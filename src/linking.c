#include "linking.h"
#include "utilself.h"

static struct elf_object_s * object_list = 0;

void object_add(struct elf_object_s * obj)
{
    obj->next = object_list;
    object_list = obj;
}

struct elf_object_s * object_first()
{
    return object_list;
}

struct elf_object_s * object_find(const char * name)
{
    struct elf_object_s * current = object_list;
    while(current)
    {
        if(my_strcmp(current->name, name) == 0)
        {
            return current;
        }
        
        current = current->next;
    }

    return 0;
}