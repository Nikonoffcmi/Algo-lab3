#include <iostream>

struct itemsList
{
    char name[10];
    int nextItem;
    int contentList;
};

struct contentList
{
    int item;
    int amount;
    int nextItem;
};

void writeItemsList(itemsList item)
{
    FILE *fp;
    if((fp=fopen("file1", "rb"))==NULL) {
    printf("Cannot open file.");
    return;
    }

    int buf[2] = {fread(fp, sizeof(int), 2, fp)};
    int active_point = buf[0];
    int active_offset;
    while (active_point!=0)
    {
        active_offset = active_point + sizeof(itemsList) - 4;
        fseek(fp, active_offset, 0);
        active_point = fread(fp, sizeof(int), 1, fp);       
    }

    
    int deleted_point = buf[1];
    int deleted_offset;
    if (deleted_point!=0)
    {
        fseek(fp, active_offset, 0);
        fclose(fp);

        if((fp=fopen("file1", "wb"))==NULL) {
        printf("Cannot open file.");
        return;
        }
        fwrite(&deleted_point,sizeof(int),1, fp);

        fseek(fp, deleted_offset, 0);
        fwrite(&item,sizeof(itemsList),1, fp);   

    }

    

}

int main()
{
    return 0;
}