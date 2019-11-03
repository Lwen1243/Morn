#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "morn_util.h"

void mJSONLoad(char *filename,MTree *tree);
char *mJSONName(MTreeNode *node);
char *mJSONValue(MTreeNode *node);
MList *mJSONGet(MTree *tree,char *name);
MTreeNode *mTreeSearch(MTreeNode *node,int (*func)(MTreeNode *,void *),void *para,int mode);

void main()
{
    MTree *json=mTreeCreate();
    mJSONLoad("./test_JSON_file.json",json);

    printf("%s��%s\n\n",mJSONName(json->treenode->child[0]),mJSONValue(json->treenode->child[0]));

    MList *list;
    list = mJSONGet(json,"������");
    for(int i=0;i<list->num;i++) printf("������%d��%s\n",i,list->data[i]);
    printf("\n");

    list = mJSONGet(json,"�ο���ʦ");
    for(int i=0;i<list->num;i++) printf("�ο���ʦ%d��%s\n",i,list->data[i]);
    printf("\n");

    list = mJSONGet(json,"ѧ��.�ɼ�.����");
    for(int i=0;i<list->num;i++) printf("�ɼ�%d��%d\n",i,atoi(list->data[i]));
    printf("\n");

    int func(MTreeNode *ptr,void *para)
    {return ((strcmp(mJSONName(ptr),"��ѧ")==0)&&(atoi(mJSONValue(ptr))>=90));}
    MTreeNode *node = json->treenode;
    while(1)
    {
        node = mTreeSearch(node,func,NULL,0);
        if(node == NULL) break;
        printf("����%s\n",mJSONValue(node->parent->parent->child[0]));
    }

    mTreeRelease(json);
}
    