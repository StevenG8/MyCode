#include <stdio.h>

#define MaxTree 10
#define Null -1
typedef int Tree ;
typedef char  ElementType ;
typedef struct TreeNode TreeNodeArray ;

struct TreeNode
{
  ElementType Element ;
  Tree Left ;
  Tree Right ;
};
struct TreeNode Tree1[MaxTree] , Tree2[MaxTree] ;


Tree BuildeTree( TreeNodeArray Tree[]  )
{
    int i,N,check[MaxTree] ;
    char cl,cr ;
    int Root ;
    scanf("%d",&N ) ;

    if( N!=0 )
    {
        for( i=0 ; i<N ; i++ ) check[i] = 0 ;
        for( i=0 ; i<N ; i++ )
        {
            scanf(" %c %c %c" , &Tree[i].Element , &cl , &cr ) ;

            if( cl != '-' )//如果结点有左孩子结点，将左孩子结点标记
            {
                Tree[i].Left = cl-'0' ;
                check[ Tree[i].Left ] = 1 ;
            }
            else Tree[i].Left = Null ;

            if( cr!= '-' )//如果结点有右孩子结点，将右孩子结点标记
             {
                 Tree[i].Right = cr-'0' ;
                 check[ Tree[i].Right ] =1 ;
             }
            else Tree[i].Right =  Null ;
        }
    }
    else
        return  Null ;

    for(i=0 ; i<N ; i++ )
    {
        if(check[ i ]==0 )
        break ;
    }
    Root = i ;

    return  Root ;
}


int Isomorphic(  Tree Root1,Tree Root2 )
{
    if( (Root1== Null) && (Root2== Null)  )
         return 1 ;
    if( ((Root1== Null)&&(Root2!= Null)) || ((Root1!= Null)&&(Root2 == Null)) )
        return 0 ;
    if( Tree1[Root1].Element != Tree2[Root2].Element  )
        return 0 ;

    if(  (Tree1[Root1].Left ==  Null) && (Tree2[Root2].Left== Null) )
        return Isomorphic( Tree1[Root1].Right,Tree2[Root2].Right ) ;

    //左子树都不为空且左子树的第一个结点元素相同，判断两棵树左子树，右子树是否分别同构
    if(  ((Tree1[Root1].Left!= Null) && (Tree2[Root2].Left!= Null))&&
         (( Tree1[ Tree1[Root1].Left ].Element==Tree2[Tree2[Root2].Left].Element ))
      )
        return ( Isomorphic(Tree1[Root1].Left,Tree2[Root2].Left) &&
                 Isomorphic( Tree1[Root1].Right,Tree2[Root2].Right ) ) ;
    else//判断一棵树的左子树与另一棵树的右子树是否同构
        return( Isomorphic( Tree1[Root1].Left,Tree2[Root2].Right ) &&
                Isomorphic( Tree1[Root1].Right,Tree2[Root2].Left ) ) ;

}


int main(  )
{
    int i ;
    Tree Root1 , Root2 ;
    Root1 = BuildeTree( Tree1 ) ;
    Root2 = BuildeTree( Tree2 ) ;
    if( Isomorphic( Root1,Root2 ) )    printf("Yes\n") ;
    else                               printf("No\n") ;
    return 0 ;

}
