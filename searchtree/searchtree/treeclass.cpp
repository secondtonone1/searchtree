// searchtree.cpp : Defines the entry point for the console application.
//
#include "treeclass.h"

void TreeClass::initial(   list<int>& data)
{
	for(   list<int>::iterator   listIter = data.begin(); listIter != data.end();
		listIter++)
	{
		TreeNode * treeNode = m_pRoot;
		if(!treeNode)
		{
			m_pRoot = new TreeNode(*listIter);
			continue;
		}

		TreeNode * nodeParent = NULL;
		bool findflag = true;
		while(treeNode)
		{
			if(treeNode->m_nData < *listIter)
			{
				nodeParent = treeNode;
				treeNode = treeNode->m_pRightChild;
			}
			else if(treeNode->m_nData >  *listIter)
			{
				nodeParent = treeNode;
				treeNode = treeNode->m_pLeftChild;
			}
			else
			{
				//找到树中有相等的节点，那么不插入，也可以完善为次数+1
				findflag = false;
				break;
			}
		}

		if(findflag)
		{
			if(nodeParent->m_nData <*listIter )
			{
				TreeNode * treeNodeTemp =new TreeNode(*listIter);

				nodeParent->m_pRightChild = treeNodeTemp;
				treeNodeTemp->m_pParent = nodeParent;
			}
			else
			{
				TreeNode * treeNodeTemp =new TreeNode(*listIter);
				nodeParent->m_pLeftChild = treeNodeTemp;
				treeNodeTemp->m_pParent = nodeParent;
			}
		}

	}


}

//中序遍历
void TreeClass::visitTree()
{
	if(!m_pRoot)
	{
		cout << "empty tree!!!";
	}

	//找到树的最小节点
	
	TreeNode * treeNodeTemp = findMinNode(m_pRoot);
	
	while(treeNodeTemp)
	{
		cout << (*treeNodeTemp);
		treeNodeTemp = findNextNode(treeNodeTemp);
	}
	
}

//寻找一个子树最小节点
TreeNode * TreeClass::findMinNode(TreeNode * root)
{
	if(!root)
	{
		return NULL;
	}
	TreeNode * treeNode = root;
	while(treeNode->m_pLeftChild)
	{
		treeNode = treeNode->m_pLeftChild;
	}

	return treeNode;
}

//寻找一个子树最大节点
TreeNode * TreeClass::findMaxNode(TreeNode * root)
{
	if(!root)
	{
		return NULL;
	}
	TreeNode * treeNode = root;
	while(treeNode->m_pRightChild)
	{
		treeNode = treeNode->m_pRightChild;
	}

	return treeNode;
}


//搜索前驱节点
TreeNode* TreeClass::findPreNode(TreeNode * treeNode)
{
	//左子树不为空，找到左子树中最大节点
	if( treeNode->m_pLeftChild )
	{
		TreeNode * treeNodeTemp = findMaxNode( treeNode->m_pLeftChild); 
		return treeNodeTemp;
	}

	//左子树为空
	//找到父节点，如果该节点是父节点的右孩子，那么父节点为前驱节点。
	//如果不满足，则将父节点设为该节点，继续向上找，知道满足条件或者父节点为空
	
	TreeNode * treeNodeTemp = treeNode->m_pParent;

	while(treeNodeTemp && treeNode != treeNodeTemp->m_pRightChild)
	{
		treeNode = treeNodeTemp;
		treeNodeTemp = treeNodeTemp ->m_pParent;
	}

	return treeNodeTemp;

}

//搜索后继节点
TreeNode * TreeClass::findNextNode(TreeNode * treeNode)
{

	//右子树不为空，找到右子树中最小节点
	if( treeNode->m_pRightChild )
	{
		TreeNode * treeNodeTemp = findMinNode( treeNode->m_pRightChild); 
		return treeNodeTemp;
	}

	//右子树为空
	//找到父节点，如果该节点是父节点的左孩子，那么父节点为后继节点。
	//如果不满足，则将父节点设为该节点，继续向上找，直到满足条件或者父节点为空

	TreeNode * treeNodeTemp = treeNode->m_pParent;

	while(treeNodeTemp && treeNode != treeNodeTemp->m_pLeftChild)
	{
		treeNode = treeNodeTemp;
		treeNodeTemp = treeNodeTemp ->m_pParent;
		
	}

	return treeNodeTemp;

}

//删除的节点没有子节点
void TreeClass::deleteNoChildNode(TreeNode * treeNode)
{
	//根节点
	if(!(treeNode->m_pParent))
	{
		m_pRoot = NULL;
		delete(treeNode);
		return;
	}

	if(treeNode->m_pParent->m_pRightChild == treeNode)
	{
		treeNode->m_pParent->m_pRightChild = NULL;
	}
	else
	{
		treeNode->m_pParent->m_pLeftChild = NULL;
	}

	delete(treeNode);
}

void TreeClass::deleteOneChildNode(TreeNode * treeNode, TreeNode * childNode)
{
	//如果是根节点
	if(treeNode->m_pParent == NULL)
	{
		m_pRoot = childNode;
		m_pRoot->m_pParent = NULL;
		delete(treeNode);
		return;
	}

	//如果不是根节点
	if(treeNode->m_pParent->m_pLeftChild == treeNode)
	{
		treeNode->m_pParent->m_pLeftChild = childNode;
		childNode->m_pParent = treeNode->m_pParent;
		delete(treeNode);
		return;
	}

	if(treeNode->m_pParent->m_pRightChild == treeNode)
	{
		treeNode->m_pParent->m_pRightChild = childNode;
		childNode->m_pParent = treeNode->m_pParent;
		delete(treeNode);
		return;
	}

}

void TreeClass::deleteTwoChildNode(TreeNode * treeNode)
{
	//找到前驱节点
	TreeNode* preNode = findPreNode(treeNode);

	preupdateNode(preNode, treeNode);


	delete(treeNode);

}

void TreeClass::preupdateNode(TreeNode * preNode, TreeNode * treeNode)
{
	
	preNode->m_pRightChild = treeNode->m_pRightChild;
	treeNode->m_pRightChild->m_pParent = preNode;
	//判断前驱节点是否为该节点的左孩子
	if(treeNode->m_pLeftChild != preNode)
	{
		TreeNode * prechild = NULL;
		if(preNode->m_pLeftChild)
		{
			prechild = preNode->m_pLeftChild;
		}

		preNode->m_pLeftChild = treeNode->m_pLeftChild;
		treeNode->m_pLeftChild->m_pParent = preNode;
		if(preNode->m_pParent->m_pLeftChild == preNode)
		{
			preNode->m_pParent->m_pLeftChild =prechild;
			if(prechild)
			{
				prechild->m_pParent = preNode->m_pParent;
			}
		}
		else
		{
			preNode->m_pParent->m_pRightChild =prechild;
			if(prechild)
			{
				prechild->m_pParent = preNode->m_pParent;
			}
		}
	}

	if(treeNode->m_pParent == NULL)
	{
		preNode->m_pParent = NULL;
		m_pRoot = preNode;
		return;
	}
	
	//节点有父节点，需要将父节点和前驱节点绑定

	preNode->m_pParent = treeNode->m_pParent;

	if(treeNode->m_pParent->m_pLeftChild == treeNode)
	{
		treeNode->m_pParent->m_pLeftChild = preNode;
	}
	else
	{
		treeNode->m_pParent->m_pRightChild = preNode;
	}

}

void TreeClass::deleteTreeNode(TreeNode* treeNode)
{
	 //没有子节点，直接删除，注意根节点的处理
	if(treeNode->m_pLeftChild == NULL && treeNode->m_pRightChild == NULL)
	{
		deleteNoChildNode(treeNode);
		return;
	}

	//只有一个子节点，将子节点替换该节点, 注意根节点处理
	if(treeNode->m_pLeftChild == NULL && treeNode->m_pRightChild != NULL)
	{
		deleteOneChildNode(treeNode, treeNode->m_pRightChild);
		return;
	}

	if(treeNode->m_pLeftChild != NULL && treeNode->m_pRightChild == NULL)
	{
		deleteOneChildNode(treeNode, treeNode->m_pLeftChild);
		return;
	}

	deleteTwoChildNode(treeNode);

}

void TreeClass::eraseNode(int i)
{
	TreeNode * treeNode = findTreeNode(i);
	deleteTreeNode(treeNode);
}

TreeNode * TreeClass::findTreeNode(int i)
{
	TreeNode *treeNode = m_pRoot;
	while(treeNode)
	{
		if(treeNode->m_nData > i)
		{
			treeNode = treeNode->m_pLeftChild;
		}
		else if(treeNode->m_nData < i)
		{
			treeNode = treeNode->m_pRightChild;
		}
		else
		{
			return treeNode;
		}
	}

	return treeNode;
}