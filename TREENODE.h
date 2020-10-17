#ifndef __TREENODE_H
#define __TREENODE_H
//���������������Ļ���������ʹ��ʱ���ֶ���TreeElemType���壬�������޸�NodePreTraverse��NodePostTraverse��NodeInTraverse��NodeLevelTraverse������
//���ڸϹ���æ��������Щ��bug���Դ˱�����б�Ǹ�����н����Խ��飬��ͨ��QQ��1345578933��ϵ������껣�20191025���й���ѧ������ѧ�� 
#include<stdio.h>
#include<stdlib.h> 
#include<math.h> 
#include"STRINGHEAP.h"
//������Ԫ���������ͣ�ȱʡint 
typedef String* TreeElemType;
struct TreeNode{
	TreeElemType data;
	TreeNode *child;
	TreeNode *sibling;
};
struct Tree{
	int length;
	int depth;
	TreeNode *p; 
};
//����Ԫ���������ͣ�TreeNode *  
typedef TreeNode* TreeQueueElemType;
struct TreeQueueNode{
	TreeQueueElemType data;
	TreeQueueNode *next;
};
struct TreeQueue{
	TreeQueueNode *rear;
	TreeQueueNode *front;
	int length;
	TreeQueueNode *p; 
};
//�������� 
int InitTree(Tree *&t){
	//��ʼ����t������һ���ǿս������ɹ�����0��t�շ���1�����շ���2  	
	t=(Tree *)malloc(sizeof(Tree));
	if(t==NULL){
		return(1);
	}
	t->p=(TreeNode *)malloc(sizeof(TreeNode));
	if(t->p==NULL){
		return(2);
	}
	t->p->child=NULL;
	t->p->sibling=NULL;
	t->length=1;
	t->depth=1;
	return(0);
}
void NodeFree(TreeNode *&p){
	//�ͷŵ���֦p��� 
	TreeNode *j,*k;
	if(p!=NULL){
		for(j=p->child;j!=NULL;){
			k=j->sibling;
			NodeFree(j);
			j=k;
		}
		free(p);
		p=NULL;
		return;
	}
	return;
} 
void DestroyTree(Tree *&t){
	//������t 
	NodeFree(t->p);
	free(t);
	t=NULL;
	return;
}
void ClearTree(Tree *&t){
	//����t�ÿգ�������  
	TreeNode *j,*k;
	t->length=1;
	t->depth=1;
	for(j=t->p->child;j!=NULL;){
		k=j->sibling;
		NodeFree(j);
		j=k;
	}
	return; 
}
int TreeEmpty(Tree *&t){
	//�ж���t�Ƿ�Ϊ�գ��Ƿ���1�����Ƿ���0 
	if(t->length==0){
		return(1);
	}
	return(0);
}
int NodeLength(TreeNode *&p,int zero){
	//����֦�ĳ��ȣ�zeroΪ��̬�����־   
	static int flag;
	TreeNode *j;
	if(zero==0){
		flag=NULL;
		return(0);
	} 
	if(p!=NULL){
		flag++;
		for(j=p->child;j!=NULL;j=j->sibling){
			NodeLength(j,1);
		}
		return(flag);
	}
	else{
		return(flag);
	}
}
int TreeLength(Tree *&t){
	//������t���� 
	return(t->length);
}
int NodeDepth(TreeNode *&p,int zero){
	//����֦����ȣ�zeroΪ��̬�����־ 
	static int flag;
	int n,i;
	TreeNode *j;
	i=0;
	if(zero==0){
		flag=NULL;
		return(0);
	} 
	if(p!=NULL){
		flag++;
		for(j=p->child;j!=NULL;j=j->sibling){
			n=NodeDepth(j,1);
			if(i<n){
				i=n;
			}
		}
		flag=n+1;
		return(flag);
	}
	else{
		return(0);
	}
}
int TreeDepth(Tree *&t){
	//������t��� 
	return(t->depth);
}
int NodeWidth(TreeNode *p,int i){
	//����֦��i��Ŀ�� 
	int flag;
	TreeNode *j;
	flag=0;
	if(p==NULL){
		return(0);
	}
	else{
		if(i==1){
			return(1);
		}
		for(j=p->child;j!=NULL;j=j->sibling){
			flag=flag+NodeWidth(j,i-1);
		}
	}
	return(flag);
}
int TreeWidth(Tree *&t,int i){
	//��������i��Ŀ�� 
	return(NodeWidth(t->p,i));
}
TreeNode *Root(Tree *&t){
	//������t����� 
	return(t->p);
}
int Value(Tree *&t,TreeNode *&p,TreeElemType &e){
	//������t��ָ��p��Ԫ��,�ɹ���ֵ��ֵ��e���ڵ�ַ������0��ʧ�ܷ���1 
	if(p==NULL){
		return(1);
	}
	e=p->data;
	return(0);
} 
int Assign(Tree *&t,TreeNode *&p,TreeElemType e){
	//����t��ָ��p��Ԫ�ظ�ֵΪe,�ɹ�����0��ʧ�ܷ���1 
	if(p==NULL){
		return(1);
	}
	p->data=e;
	return(0);
}
TreeNode *NodeParent(TreeNode *&j,TreeNode *&p,int zero){
	//������֦j��ָ��p��Ԫ�صĸ���㣬zeroΪ��̬�����־���ɹ�������Ӧָ�룬ʧ�ܷ���NULL 
	static TreeNode *flag;
	TreeNode *l;
	if(zero==0){
		flag=NULL;
		return(flag);
	} 
	if(j==NULL){
		return(j);
	}
	if(flag==NULL){
		for(l=j->child;l!=NULL;l=l->sibling){
			flag=NodeParent(l,p,1);
			if(flag!=NULL){
				break;
			}
		}
		return(flag);
	}
	if(flag!=NULL){
		return(flag);
	} 
	if(flag==NULL){
		for(l=j->child;l!=NULL;l=l->sibling){
			if(l==p){
				flag=j;
				return(flag);
			}
		}
		return(flag);
	}
}
TreeNode *Parent(Tree *&t,TreeNode *&p){
	//������t��ָ��p��Ԫ�صĸ���㣬�ɹ�������Ӧָ�룬ʧ�ܷ���NULL  
	NodeParent(t->p,p,0);
	return(NodeParent(t->p,p,1));
}
TreeNode *Child(Tree *&t,TreeNode *&p,int i){
	//������t��ָ��p��Ԫ�صĵ�i���ӽ�㣬�ɹ�������Ӧָ�룬ʧ�ܷ���NULL  
	int width,flag1;
	TreeNode *flag2; 
	width=0;
	for(flag2=p->child;flag2!=NULL;flag2=flag2->sibling){
		width++;
	}
	if(i<0||i>width){
		return(NULL);
	}
	for(flag1=0,flag2=p->child;flag1<i-1;flag1++,flag2=flag2->sibling){
	}
	return(flag2);
}
TreeNode *LeftSibling(Tree *&t,TreeNode *&p){
	//������t��ָ��p��Ԫ�ص����ֵܽ�㣬�ɹ�������Ӧָ�룬ʧ�ܷ���NULL 
	TreeNode *q,*j,*k;
	NodeParent(t->p,p,0);
	q=NodeParent(t->p,p,1);
	if(p==q->child){
		return(NULL);
	}
	for(j=q->child;j!=NULL;j=j->sibling){
		if(j->sibling==p){
			return(j);
		}
	}
	return(NULL);
}
TreeNode *RightSibling(Tree *&t,TreeNode *&p){
	//������t��ָ��p��Ԫ�ص����ֵܽ�㣬�ɹ�������Ӧָ�룬ʧ�ܷ���NULL 
	return(p->sibling);
}
int InsertChild(Tree *&t,TreeNode *&p,int i,TreeNode *&v){
	//����t��ָ��p��Ԫ�����iλ��ǰ����ϵv����iΪ0�����ں󷽲��롣�ɹ�����0��ʧ�ܷ���1 
	int width,flag1;
	TreeNode *flag2;
	width=0;
	for(flag2=p->child;flag2!=NULL;flag2=flag2->sibling){
		width++;
	}
	if(i<0||i>width){
		return(1);
	}
	if(i==0){
		for(flag2=p->child;flag2->sibling!=NULL;flag2=flag2->sibling){
			flag2->sibling=v;
	    	NodeLength(v,0);
	    	t->length=t->length+NodeLength(v,1);
	        NodeDepth(v,0);
		    t->depth=t->depth+NodeDepth(v,1);
		    return(0);
		}
	}
	else{
		if(i==1){
			v->sibling=p->child;
			p->child=v;
	    	NodeLength(v,0);
	    	t->length=t->length+NodeLength(v,1);
	        NodeDepth(v,0);
		    t->depth=t->depth+NodeDepth(v,1);
			return(0);
		}
		else{
			for(flag1=0,flag2=p->child;flag1<i-2;flag1++,flag2=flag2->sibling){
			}
			v->sibling=flag2->sibling;
			flag2->sibling=v;
	    	NodeLength(v,0);
	    	t->length=t->length+NodeLength(v,1);
	        NodeDepth(v,0);
		    t->depth=t->depth+NodeDepth(v,1);
			return(0);
		}
	}
}
int DeleteChild(Tree *&t,TreeNode *&p,int i,TreeNode *&v){
	//����t��ָ��p��Ԫ��ɾ��iλ����ϵ������ֵ��v���ɹ�����0��ʧ�ܷ���1 
	int width,flag1;
	TreeNode *flag2;
	width=0;
	for(flag2=p->child;flag2!=NULL;flag2=flag2->sibling){
		width++;
	}
	if(i<0||i>width){
		return(1);
	}
	if(i==1){
		NodeLength(p->child,0);
		t->length=t->length-NodeLength(p->child,1);
		NodeDepth(p->child,0);
		t->depth=t->depth-NodeDepth(p->child,1);
		v=p->child;
		p->child=p->child->sibling;
		v->sibling=NULL;
		return(0);
	}
	else{
		for(flag1=0,flag2=p->child;flag1<i-2;flag1++,flag2=flag2->sibling){
		}
		NodeLength(flag2->sibling,0);
		t->length=t->length-NodeLength(flag2->sibling,1);
	    NodeDepth(flag2->sibling,0);
	    t->depth=t->depth-NodeDepth(flag2->sibling,1);
	    v=flag2->sibling;
	    flag2->sibling=flag2->sibling->sibling;
	    v->sibling=NULL;
		return(0);
	}
}
int NodeCopy(TreeNode *&p,TreeNode *&q,int zero){
	//������֦p��q���ɹ�����0��ʧ�ܷ���1��zeroΪ��̬�����־  
	static int err;
	TreeNode *j;
	if(zero==0){
		err=0;
		return(0);
	} 
	if(p!=NULL){
		q->data=p->data;
		q->child=(TreeNode *)malloc(sizeof(TreeNode));
		q->sibling=(TreeNode *)malloc(sizeof(TreeNode));
		if(q->child==NULL||q->sibling==NULL){
			err=1;
			return(1);
		}
		for(j=p->child;;j=j->sibling){
			NodeCopy(j,q->sibling,1);
			if(j==NULL){
				break;
			}
		}
		return(0);
	}
	if(p==NULL){
		free(q);
		q=NULL;
	}
	if(err==1){
		return(1);
	}
	return(0);
}
int TreeCopy(Tree *&t,Tree *&u){
	//������t��p���ɹ�����0��ʧ�ܷ���1
	int err;
	ClearTree(u);
	NodeCopy(t->p,u->p,0);
	err=NodeCopy(t->p,u->p,1);
	return(err);
}
void NodePreTraverse(TreeNode *&p){
	//���������֦p����������ִ���Զ������ 
	TreeNode *j;
	if(p!=NULL){
		//�Զ��������ȱʡ��ӡ
		printf("%d\n",p->data); 
		for(j=p->child;j!=NULL;j=j->sibling){
			NodePreTraverse(j);
		}
		return;
	}
	return;
}
void PreTraverseTree(Tree *&t){
	//�������t����������ִ���Զ������ 
	NodePreTraverse(t->p);
	return;
}
void NodePostTraverse(TreeNode *&p){
	//���������֦p����������ִ���Զ������ 
	TreeNode *j;
	if(p!=NULL){
		for(j=p->child;j!=NULL;j=j->sibling){
			NodePostTraverse(j);
		}
		//�Զ��������ȱʡ��ӡ
		printf("%d\n",p->data);  
		return;
	}
	return;
}
void PostTraverseTree(Tree *&t){
	//�������t����������ִ���Զ������ 
	NodePostTraverse(t->p);
	return;
}
int InitTreeQueue(TreeQueue *&q){
	//��ʼ�����������q������һ���ս�㡣�ɹ�����0��l�շ���1�����շ���2  
	q=(TreeQueue *)malloc(sizeof(TreeQueue));
	if(q==NULL){
		return(1);
	}
	q->p=(TreeQueueNode *)malloc(sizeof(TreeQueueNode)); 
	if(q->p==NULL){
		return(2);
	}
	q->p->next=NULL; 
	q->front=q->p->next;
	q->rear=q->p;
	q->length=0;
	return(0); 
}
void DestroyTreeQueue(TreeQueue *&q){
	//���ٵ��������q  
	TreeQueueNode *flag,*res;
	flag=q->p;
	while(flag!=NULL){
		res=flag;
		flag=flag->next;
		free(res);
	}
	free(q);
	return;
}
int Enter(TreeQueue *&q,TreeQueueElemType e){
	//��e����q���ɹ�����0��ʧ�ܷ���1  
	TreeQueueNode *j,*a;
	j=(TreeQueueNode *)malloc(sizeof(TreeQueueNode));
	if(j==NULL){
		return(1);
	}
	j->data=e;
	j->next=NULL;
	a=q->rear;
	a->next=j;
	q->rear=j;
	if(q->length==0){
		q->front=q->p->next;
	}
	q->length++;
	return(0);
}
void Depart(TreeQueue *&q,TreeQueueElemType &e){
	//ɾ��q����Ԫ�ز���ֵ��e���ɹ�����0��ʧ�ܷ���1  
	TreeQueueNode *j,*a;
	j=q->front;
	a=j->next;
	q->p->next=a;
	q->front=a;
	free(j);
	q->length--;
	return;
}
int LevelTraverseTree(Tree *&t){
	//�������t����������ִ���Զ���������ɹ�����0����ʼ������ʧ�ܷ���1���������ʧ�ܷ���2 
	int err;
	TreeQueue *q;
	TreeQueueElemType e;
	TreeNode *j;
	e=t->p;
	err=InitTreeQueue(q);
	if(err!=0){
		return(1); 
	}
	err=Enter(q,e);
	if(err!=0){
		return(2); 
	}
	while(q->length!=0){
		//�Զ��������ȱʡ��ӡ 
		printf("%d\n",q->front->data);  
		for(j=q->front->data->child;j!=NULL;j=j->sibling){
		    err=Enter(q,j);
		    if(err!=0){
	    		return(2); 
	    	}
		}
		Depart(q,e);
	}
	DestroyTreeQueue(q);
	return(0);
}
#endif
