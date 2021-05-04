#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char* name, *ID, *gender;
    struct node* left, *right, *p_node;
};


void pre_printname(struct node* t)
{
	if(t)
	{
        if(t->left!=NULL)
            printf("左學弟妹: %s -> %s \n", t->name, t->left->name);
        if(t->right!=NULL)
            printf("右學弟妹: %s -> %s \n", t->name, t->right->name);
		pre_printname(t->left);
		pre_printname(t->right);
	}
}


void pre_findnode(struct node* head, const char* head_name, struct node** tmp)
{
	if(head)
	{
		
        if(strcmp(head->name, head_name)==0){
            *tmp = head;
        }else{
            pre_findnode(head->left, head_name, tmp);
            pre_findnode(head->right, head_name, tmp);
        }
	}
}

void pre_findnode_id(struct node* head, const char* head_id, struct node** tmp)
{
	if(head)
	{
        if(strcmp(head->ID, head_id)==0){
            *tmp = head;
        }else{
            pre_findnode_id(head->left, head_id, tmp);
            pre_findnode_id(head->right, head_id, tmp);
        }
	}
}

void delete_node(struct node* head, const char* head_id)
{
	if(head)
	{
        if(head->left && strcmp(head->left->ID, head_id)==0){
            free(head->left);
            head->left = NULL;
        }else if(head->right && strcmp(head->right->ID, head_id)==0){
            free(head->right);
            head->right = NULL;
        }
		delete_node(head->left, head_id);
		delete_node(head->right, head_id);
	}
}

int main(){
    struct node* input_arr[15];
    int c4=0, c3=1, c2=3, c1=7;
    struct node* head = NULL;
    for(int i=0;i<15;i++)
        input_arr[i] = NULL;


    printf("請問要輸入多少筆資料？");
    char data_len[5];
    scanf("%s", data_len);
    
    for(int i=0;i<atoi(data_len);i++){
        struct node* p = (struct node*) malloc(sizeof(struct node));
        p->name = (char*)malloc(256* sizeof(char));
        p->ID = (char*)malloc(256* sizeof(char));
        p->gender = (char*)malloc(256* sizeof(char));
        p->p_node = NULL;
        p->left = NULL;
        p->right = NULL;
        printf("第 %d :", i+1);
        scanf("%s %s %s", p->name, p->ID, p->gender);

        if(p->ID[2] == '6'){
            input_arr[c4] = p;
            c4++;
        }else if(p->ID[2] == '7'){
            input_arr[c3] = p;
            c3++;
        }else if(p->ID[2] == '8'){
            input_arr[c2] = p;
            c2++;
        }else if(p->ID[2] == '9'){
            input_arr[c1] = p;
            c1++;
        }
    }

    for(int i=0;i<7;i++){
        if(input_arr[i]){
            input_arr[i]->left = input_arr[2*i+1];
            input_arr[i]->right = input_arr[2*i+2];
            if(input_arr[2*i+1]!=NULL)
                input_arr[2*i+1]->p_node = input_arr[i];
            if(input_arr[2*i+2]!=NULL)
                input_arr[2*i+2]->p_node = input_arr[i];
        }
    }

    head = input_arr[0];

    while(true) 
    {
        char cmd[5];

        printf("\nq=quit, n=建立節點, d=刪除節點, p=印直屬學長姐、學弟妹, P=印出所有的直屬學弟妹、m=修改名字\n");
        scanf("%s", cmd);
        if(cmd[0] == 'q')
            break;
        else if(cmd[0] == 'P'){
            struct node* tmp = NULL;
            char name[256];
            printf("請輸入要找的 node name: \n");
            scanf("%s", name);

            pre_findnode(head, name, &tmp);
            if(tmp){
                pre_printname(tmp);
            }else{
                 puts("找不到\n");
            }
        }else if(cmd[0] == 'p'){
            struct node* tmp = NULL;
            char name[256];
            printf("請輸入要找的 node name: \n");
            scanf("%s", name);
            pre_findnode(head, name, &tmp);

            if(tmp){
                char p_name[256], c1_name[256], c2_name[256];
                strcpy(p_name, "");
                strcpy(c1_name, "");
                strcpy(c2_name, "");
                if(tmp->p_node !=NULL)
                    strcpy(p_name, tmp->p_node->name);
                if(tmp->left!=NULL)
                    strcpy(c1_name, tmp->left->name);
                if(tmp->right!=NULL)
                    strcpy(c2_name, tmp->right->name);
                printf("學長姐: %s\n左學弟妹: %s\n右學弟妹: %s \n", p_name, c1_name, c2_name);
            }else{
                 puts("找不到\n");
            }
        }else if(cmd[0] == 'd'){
            printf("請輸入要刪除的 node id: \n");
            char id[256];
            scanf("%s", id);
            delete_node(head, id);

        }else if(cmd[0] == 'm'){
            printf("請輸入要更改的 node id: \n");
            char id[256], name[256];
            scanf("%s", id);
            printf("請輸入要更改的 name: \n");
            scanf("%s", name);

            struct node* tmp = NULL;
            pre_findnode_id(head, id, &tmp);
            if(tmp){
                strcpy(tmp->name, name);
            }else{
                 puts("找不到\n");
            }
        }
    }
    return 0;
}

