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
				//�ҵ���������ȵĽڵ㣬��ô�����룬Ҳ��������Ϊ����+1
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

//�������
void TreeClass::visitTree()
{
	if(!m_pRoot)
	{
		cout << "empty tree!!!";
	}

	//�ҵ�������С�ڵ�
	
	TreeNode * treeNodeTemp = findMinNode(m_pRoot);
	
	while(treeNodeTemp)
	{
		cout << (*treeNodeTemp);
		treeNodeTemp = findNextNode(treeNodeTemp);
	}
	
}

//Ѱ��һ��������С�ڵ�
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

//Ѱ��һ���������ڵ�
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


//����ǰ���ڵ�
TreeNode* TreeClass::findPreNode(TreeNode * treeNode)
{
	//��������Ϊ�գ��ҵ������������ڵ�
	if( treeNode->m_pLeftChild )
	{
		TreeNode * treeNodeTemp = findMaxNode( treeNode->m_pLeftChild); 
		return treeNodeTemp;
	}

	//������Ϊ��
	//�ҵ����ڵ㣬����ýڵ��Ǹ��ڵ���Һ��ӣ���ô���ڵ�Ϊǰ���ڵ㡣
	//��������㣬�򽫸��ڵ���Ϊ�ýڵ㣬���������ң�֪�������������߸��ڵ�Ϊ��
	
	TreeNode * treeNodeTemp = treeNode->m_pParent;

	while(treeNodeTemp && treeNode != treeNodeTemp->m_pRightChild)
	{
		treeNode = treeNodeTemp;
		treeNodeTemp = treeNodeTemp ->m_pParent;
	}

	return treeNodeTemp;

}

//������̽ڵ�
TreeNode * TreeClass::findNextNode(TreeNode * treeNode)
{

	//��������Ϊ�գ��ҵ�����������С�ڵ�
	if( treeNode->m_pRightChild )
	{
		TreeNode * treeNodeTemp = findMinNode( treeNode->m_pRightChild); 
		return treeNodeTemp;
	}

	//������Ϊ��
	//�ҵ����ڵ㣬����ýڵ��Ǹ��ڵ�����ӣ���ô���ڵ�Ϊ��̽ڵ㡣
	//��������㣬�򽫸��ڵ���Ϊ�ýڵ㣬���������ң�ֱ�������������߸��ڵ�Ϊ��

	TreeNode * treeNodeTemp = treeNode->m_pParent;

	while(treeNodeTemp && treeNode != treeNodeTemp->m_pLeftChild)
	{
		treeNode = treeNodeTemp;
		treeNodeTemp = treeNodeTemp ->m_pParent;
		
	}

	return treeNodeTemp;

}

//ɾ���Ľڵ�û���ӽڵ�
void TreeClass::deleteNoChildNode(TreeNode * treeNode)
{
	//���ڵ�
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
	//����Ǹ��ڵ�
	if(treeNode->m_pParent == NULL)
	{
		m_pRoot = childNode;
		m_pRoot->m_pParent = NULL;
		delete(treeNode);
		return;
	}

	//������Ǹ��ڵ�
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
	//�ҵ�ǰ���ڵ�
	TreeNode* preNode = findPreNode(treeNode);

	preupdateNode(preNode, treeNode);


	delete(treeNode);

}

void TreeClass::preupdateNode(TreeNode * preNode, TreeNode * treeNode)
{
	
	preNode->m_pRightChild = treeNode->m_pRightChild;
	treeNode->m_pRightChild->m_pParent = preNode;
	//�ж�ǰ���ڵ��Ƿ�Ϊ�ýڵ������
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
	
	//�ڵ��и��ڵ㣬��Ҫ�����ڵ��ǰ���ڵ��

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
	 //û���ӽڵ㣬ֱ��ɾ����ע����ڵ�Ĵ���
	if(treeNode->m_pLeftChild == NULL && treeNode->m_pRightChild == NULL)
	{
		deleteNoChildNode(treeNode);
		return;
	}

	//ֻ��һ���ӽڵ㣬���ӽڵ��滻�ýڵ�, ע����ڵ㴦��
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