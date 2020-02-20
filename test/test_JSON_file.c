/*
Copyright (C) 2019  JingWeiZhangHuai
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
//���룺 gcc -O2 -fopenmp test_JSON_file.c -I ..\include\ -L ..\lib\x64\mingw -lmorn -o test_JSON_file.exe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "morn_util.h"

void mJSONLoad(char *filename,MTree *tree);
char *mJSONName(MTreeNode *node);
char *mJSONValue(MTreeNode *node);
void mJSONSearch(MTree *tree,MList *result,char *name);
MTreeNode *mTreeSearch(MTreeNode *node,int (*func)(MTreeNode *,void *),void *para,int mode);

void main()
{
    MTree *json=mTreeCreate();
    mJSONLoad("./test_JSON_file.json",json);

    MTreeNode *node = json->treenode->child[0];
    for(int i=0;i<node->child_num;i++)
        printf("%s��%s\n",mJSONName(node->child[i]),mJSONValue(node->child[i]));
    printf("\n");
    
    MList *list = mListCreate(DFLT,NULL);
    
    mJSONSearch(json,list,"������");
    for(int i=0;i<list->num;i++) printf("������%d��%s\n",i,list->data[i]);
    printf("\n");

    mJSONSearch(json,list,"�ο���ʦ");
    for(int i=0;i<list->num;i++) printf("�ο���ʦ%d��%s\n",i,list->data[i]);
    printf("\n");

    MList *name = mListCreate(DFLT,NULL);mJSONSearch(json,name,"ѧ��.����");
    MList *score= mListCreate(DFLT,NULL);mJSONSearch(json,score,"ѧ��.�ɼ�.��ѧ");
    for(int i=0;i<name->num;i++) printf("%s����ѧ�ɼ���%d\n",name->data[i],atoi(score->data[i]));
    mListRelease(name);
    mListRelease(score);
    printf("\n");

    int func(MTreeNode *ptr,void *para)
    {return ((strcmp(mJSONName(ptr),"��ѧ")==0)&&(atoi(mJSONValue(ptr))>=90));}
    node = json->treenode;
    while(1)
    {
        node = mTreeSearch(node,func,NULL,0);
        if(node == NULL) break;
        printf("����%s\n",mJSONValue(node->parent->parent->child[0]));
    }

    mListRelease(list);
    mTreeRelease(json);
}
    