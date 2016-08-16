#include "arguments.h"

struct node {
	struct arguments *job;
	struct node *next;
	struct node *prev;
};

static DEFINE_MUTEX(list_lock); //protects list and counter
struct node *head;
int counter;


void print_list(struct node **head) {
    	struct node *temp;
    	temp=*head;
    	while(temp!=NULL) {
		print_args(temp->job);
        	temp=temp->next;
    	}
}

struct node* allocate_node(void) {
	struct node *temp;
 	temp = (struct node*)kmalloc(sizeof(struct node), GFP_KERNEL);
 	if(temp==NULL) {
        	printk("Error Allocating node\n");
        	return NULL;
    	}
	temp->job=NULL;
    	temp->next=NULL;
    	temp->prev=NULL;
    	return temp;
}


void delete_node(struct node *old) {
	free_arguments(old->job);
	kfree(old);
}

int delete_job(struct node **head, int job_id) {
    struct node *temp, *prev, *next;
    if((*head)==NULL) {
        printk("Error head is NULL\n");
        return -ENODATA;
    } else {
        temp=*head;
        while(temp!=NULL) {
            if(temp->job->unique_code==job_id) {
                if(temp==*head) {
                    next = temp->next;
                    temp->next=NULL;
                    delete_node(temp);
                    *head = next;
                    if(*head)
                        (*head)->prev=NULL;
                    return 0;
                } else {
                    prev=temp->prev;
                    next=temp->next;
                    temp->prev=NULL;
                    temp->next=NULL;
                    prev->next=next;
                    if(next)
                        next->prev=prev;
                    delete_node(temp);
                    return 0;
                }
            }
            temp=temp->next;
        }
    }
    printk("deleted nothing\n");
    return -ENODATA;
}

void insert_node(struct node **head, struct node *new) {
	struct node *temp;
	if((*head)==NULL)
        	*head=new;
    	else {
        	temp=*head;
        	while(temp->next!=NULL)
            		temp=temp->next;
        	temp->next=new;
        	new->prev=temp;
    	}
}


struct node* get_head_of_list(struct node **head) {
	if((*head)==NULL)
		return NULL;
	else {
		struct node *temp;
		temp = *head;
		*head = (*head)->next;
		temp->next=NULL;
		if((*head))
			(*head)->prev = NULL;
		return temp;
	}
}

int reorder_list(struct node **head, int pos, int val) {
        int err=0, curr_pos=0, found_at=0;
        bool found=false;
        struct node *temp, *temp1;
        if((*head)==NULL) {
                err = -ENODATA;
                goto out;
        }
        temp = (*head);
        while(temp!=NULL) {
                curr_pos++;
                if(temp->job->unique_code==val) {
                        found = true;
                        found_at = curr_pos;
                        break;
                }
                temp = temp->next;
        }

        if(!found) {
                printk("Not Found\n");
                err = -ENODATA ;
                goto out;
        }

        if (pos == found_at) {
                printk("Nothing to change\n");
                return 0;
        }
        curr_pos=0;
        temp1 = (*head);
        while(temp1!=NULL) {
                curr_pos++;
                if(curr_pos==pos)
                        break;
                temp1 = temp1->next;
        }
        if(pos>found_at) {
                if(found_at == 1)
                        (*head) = temp->next;
                if(!temp1->next) { /*inserted at end*/
			if(temp->prev)
                                temp->prev->next = temp->next;
                        if(temp->next)
                                temp->next->prev = temp->prev;
                        temp->prev = temp1;
                        temp1->next = temp;
                        temp->next = NULL;
                        return err;
                }
                temp1 = temp1->next;
        }
        if(temp->prev)
                temp->prev->next = temp->next;
        if(temp->next)
                temp->next->prev = temp->prev;
        if(temp1->prev)
                temp1->prev->next = temp;
        temp->prev = temp1->prev;
        temp1->prev = temp;
        temp->next = temp1;
        if(pos==1)  /*inserting at first*/
                (*head) = temp;
out:
        return err;
}




void delete_entire_list(struct node **head) {
	struct node *temp1, *temp2;
    	temp1 = *head;
    	temp2=NULL;
    	if(temp1)
        	temp2 = temp1->next;
    	while(temp1!=NULL) {
        	delete_node(temp1);
        	temp1=temp2;
        	if(temp1)
            		temp2 = temp1->next;
    	}
    	*head=NULL;	
}
