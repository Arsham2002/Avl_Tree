#include<iostream>
#include <cstdlib>
using namespace std;
void clear_screen()
{
   #ifdef WINDOWS
      std::system("cls");
   #else
      std::system ("clear");
   #endif
}
struct avl 
{
   int d;
   struct avl* l;
   struct avl* r;
};
class avl_tree
{
   public:
      avl* tree = NULL;
      int height(avl*);
      int difference(avl*);
      avl* rr_rotat(avl*);
      avl* ll_rotat(avl*);
      avl* lr_rotat(avl*);
      avl* rl_rotat(avl*);
      avl* balance(avl*);
      avl* insert(avl*, int);
      avl* del(avl*,int);
      void free(avl*);
      void inorder(avl*);
      void preorder(avl*);
      void postorder(avl*);
};
int avl_tree::height(avl* t)
{
   int h = 0;
   if (t != NULL) 
   {
      int l_height = height(t->l);
      int r_height = height(t->r);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}
int avl_tree::difference(avl* t)
{
   int l_height = height(t->l);
   int r_height = height(t->r);
   int b_factor = l_height - r_height;
   return b_factor;
}
avl* avl_tree::rr_rotat(avl* parent)
{
   avl* t;
   t = parent->r;
   parent->r = t->l;
   t->l = parent;
   return t;
}
avl* avl_tree::ll_rotat(avl* parent)
{
   avl* t;
   t = parent->l;
   parent->l = t->r;
   t->r = parent;
   return t;
}
avl* avl_tree::lr_rotat(avl* parent)
{
   avl* t;
   t = parent->l;
   parent->l = rr_rotat(t);
   return ll_rotat(parent);
}
avl* avl_tree::rl_rotat(avl* parent)
{ 
   avl* t;
   t = parent->r;
   parent->r = ll_rotat(t);
   return rr_rotat(parent);
}
avl* avl_tree::balance(avl* t)
{
   int bal_factor = difference(t);
   if(bal_factor > 1)
   {
      if (difference(t->l) > 0)
         t = ll_rotat(t);
      else
         t = lr_rotat(t);
   } 
   else if (bal_factor < -1)
   {
      if(difference(t->r) > 0)
         t = rl_rotat(t);
      else
         t = rr_rotat(t);
   }
   return t;
}
avl* avl_tree::insert(avl* t, int v)
{
   if (t == NULL)  
   {
      t = new avl;
      t->d = v;
      t->l = NULL;
      t->r = NULL;
   }
   else if (v < t->d)
   {
      t->l = insert(t->l, v);
      t = balance(t);
   } 
   else if (v >= t->d)
   {
      t->r = insert(t->r, v);
      t = balance(t);
   }
   return t;
}
avl* avl_tree::del(avl* t,int x)
{
   avl *p;

   if(t == NULL)
   {
      cout << "This element does not exist" << endl;
      return NULL;
   }
   if(x > t->d)    
   {
      t->r = del(t->r,x);
      if(difference(t) == 2)
         if(difference(t->l) >= 0)
            t = ll_rotat(t);
         else
            t = lr_rotat(t);
   }
   else if(x < t -> d)
   {
      t -> l = del(t->l,x);
      if(difference(t) == -2)    
         if(difference(t->r) <= 0)
            t =rr_rotat(t);
         else
            t =rl_rotat(t);
   }
   else
   {
      if(t->r != NULL)
      {
         p = t->r;

         while(p->l != NULL)
            p = p->l;

         t->d = p->d;
         t->r = del(t->r,p->d);

         if(difference(t) == 2)
            if(difference (t->l) >= 0)
               t =ll_rotat(t);
            else
               t =lr_rotat(t);
      }
      else
         return t->l;
   }
   return t;
}
void avl_tree::free(avl* t)
{
   if(t == NULL)
      return;
   free(t -> l);
   free(t -> r);
   delete t;
}
void avl_tree::inorder(avl *t)
{
   if (t == NULL)
      return;
   inorder(t->l);
   cout << t->d << " ";
   inorder(t->r);
}
void avl_tree::preorder(avl *t)
{
   if (t == NULL)
      return;
   cout << t->d << " ";
   preorder(t->l);
   preorder(t->r);
}
void avl_tree::postorder(avl *t)
{
   if (t == NULL)
      return;
   postorder(t ->l);
   postorder(t ->r);
   cout << t->d << " ";
}
int main() {
   int c = 0, i;
   avl_tree avl;
   while (c != 6)
   {
      clear_screen();
      cout << "1.Insert Element into the tree" << endl;
      cout << "2.Delete Element from the tree" << endl;
      cout << "3.InOrder traversal" << endl;
      cout << "4.PreOrder traversal" << endl;
      cout << "5.PostOrder traversal" << endl;
      cout << "6.Exit" << endl;
      cout << "Enter your Choice: ";
      cin >> c;
      switch (c) 
      {
         case 1:
            cout << "Enter value to be inserted: ";
            cin >> i;
            avl.tree = avl.insert(avl.tree, i);
         break;
         case 2:
            cout << "Enter value to be deleted: ";
            cin >> i;
            avl.tree = avl.del(avl.tree, i);
         break;
         case 3:
            cout << "Inorder Traversal:" << endl;
            avl.inorder(avl.tree);
            cout << endl;
         break;
         case 4:
            cout << "Preorder Traversal:" << endl;
            avl.preorder(avl.tree);
            cout << endl;
         break;
         case 5:
            cout << "Postorder Traversal:" << endl;
            avl.postorder(avl.tree);
            cout << endl;
         break;
         case 6:
            free(avl.tree);
         break;
         default:
            cout << "Wrong Choice" << endl;
      }
      cin.ignore();
      if(c != 6 && c != 1)
      {
         cout << "press Enter to continue";
         cin.get();
      }
   }
   return 0;
}