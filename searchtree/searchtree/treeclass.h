// searchtree.cpp : Defines the entry point for the console application.
//
#ifndef __TREECLASS__H__
#define __TREECLASS__H__
#include<iostream>
using namespace std;
#include<list>
#include<vector>

class TreeNode
{
public:
	TreeNode():m_pParent(NULL), m_pLeftChild(NULL), m_pRightChild(NULL), m_nData(0){}
	TreeNode(const TreeNode & tree){
		this->m_nData = tree.m_nData;
		this->m_pParent = NULL;
		this->m_pLeftChild = NULL;
		this->m_pRightChild = NULL;
	}

	TreeNode(int data):m_nData(data), m_pRightChild(NULL), m_pLeftChild(NULL), m_pParent(NULL){}
	~TreeNode(){ 
		this->m_nData = 0;
		this->m_pLeftChild = NULL;
		this->m_pParent = NULL;
		this->m_pRightChild = NULL;
	}

	TreeNode& operator =(const TreeNode& treeNode)//��ֵ�����
	{
		
		if (this != &treeNode)
		{
			this->m_pParent = treeNode.m_pParent;
			this->m_pLeftChild = treeNode.m_pLeftChild;
			this->m_pRightChild = treeNode.m_pRightChild;
			this->m_nData = treeNode.m_nData;
		}
		return *this;
	} 

	
		
	friend ostream & operator<<(ostream &out, TreeNode &obj)
	{
		out <<  " " << obj.m_nData <<" ";
		return out;
	}


	TreeNode * m_pParent;
	TreeNode * m_pLeftChild;
	TreeNode * m_pRightChild;
	int m_nData;	
};



class TreeClass
{
public:
	TreeClass():m_pRoot(NULL){}
	~TreeClass(){
		
		if(!m_pRoot)
		{
			return;
		}

		//�ҵ�������С�ڵ�

		TreeNode * treeNodeTemp = findMinNode(m_pRoot);
		vector<TreeNode *> treenodeVec;
		while(treeNodeTemp)
		{
			treenodeVec.push_back(treeNodeTemp);
			treeNodeTemp = findNextNode(treeNodeTemp);
			
		}

		for(int i = 0; i < treenodeVec.size(); i++)
		{
			delete(treenodeVec[i]);
		}

		treenodeVec.clear();
		m_pRoot = NULL;
	}
	
	void initial(   list<int>& data);

	void visitTree();

	//����ǰ�̽ڵ�
	TreeNode *findPreNode(TreeNode * treeNode);

	//������̽ڵ�
	TreeNode * findNextNode(TreeNode * treeNode);

	//Ѱ��һ��������С�ڵ�
	TreeNode * findMinNode(TreeNode * root);
	//Ѱ��һ���������ڵ�
	TreeNode * findMaxNode(TreeNode * root);
	
	//ɾ��һ���ڵ�
	void deleteTreeNode(TreeNode* treeNode);

	//ɾ���Ľڵ�û���ӽڵ�
	void deleteNoChildNode(TreeNode * treeNode);
	//ɾ���Ľڵ���һ���ӽڵ�
	void deleteOneChildNode(TreeNode * treeNode, TreeNode * childNode);
	//ɾ���ڵ�����������,�ҵ���̽ڵ����ǰ���ڵ��滻���ɣ�����ѡ��ǰ���ڵ�
	void deleteTwoChildNode(TreeNode * treeNode);
	//��ǰ���ڵ��滻��ǰ�ڵ�
	void preupdateNode(TreeNode * preNode, TreeNode * treeNode);

	void eraseNode(int i);

	TreeNode * findTreeNode(int i);

	TreeNode * m_pRoot;
};





#endif

