#include "XmlParse.h"
#include "rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

void XmlParse::InitXml(rapidxml::xml_document<> &doc)
{
	xml_node<> *node = doc.allocate_node(node_declaration, "", "");
	doc.append_node(node);
	xml_attribute<> *attr1 = doc.allocate_attribute("version", "1.0");
	xml_attribute<> *attr2 = doc.allocate_attribute("encoding", "UTF-8");
	node->append_attribute(attr1);
	node->append_attribute(attr2);
}

xml_node<> *XmlParse::AppendNode(const std::string &NewNodeName, const std::string &NewNodeValue,
								 xml_document<> &doc, xml_node<> *ParentNode )
{
	xml_node<> *node = doc.allocate_node(node_element, doc.allocate_string(NewNodeName.c_str()),
		doc.allocate_string(NewNodeValue.c_str()));
	if (ParentNode == NULL)
	{			
		doc.append_node(node);			
	}
	else
	{
		ParentNode->append_node(node);
	}
	return node;
}

void XmlParse::AppendAttribute(const std::string &NewAttributeName, const std::string &NewAttributeValue,
							   xml_document<> &doc, xml_node<> *ParentNode)
{
	xml_attribute<> *attr = doc.allocate_attribute(doc.allocate_string(NewAttributeName.c_str()), 
		doc.allocate_string(NewAttributeValue.c_str()));
	if (ParentNode)
	{
		ParentNode->append_attribute(attr);
	}
}

std::string XmlParse::GetXmlAttribute( const std::string& attributeName, rapidxml::xml_node<>* node,bool isThrow )
{
	return this_type::GetXmlAttributeImpl(attributeName,node,isThrow);
}

std::string XmlParse::GetXmlAttributeImpl(const std::string& attributeName, rapidxml::xml_node<>* node,bool isThrow)
{
	assert( !attributeName.empty() );
	assert( NULL != node );

	xml_attribute<char>* attribute = node->first_attribute(attributeName.c_str());

	std::string result;

	if( NULL != attribute )
	{
		result = attribute->value();
	}
	else
	{
		if(isThrow)
		{
			std::string text = "Can't find the attribute \'" + attributeName + "\'";
			//TODO:抛出异常OR写Log
			fprintf(stderr,"Can't find the attribute %s\n",attributeName.c_str());
		}
	}

	return result;
}

xml_node<> *XmlParse::FindFirstNode(xml_document<> &doc, std::string NodeName)
{
	return NodeFind(doc, NodeName, doc.first_node());
}

xml_node<> *XmlParse::FindNextSameValueNode(xml_document<> &doc, xml_node<> *CurNode)
{
	return NextNodeFind(doc, CurNode, doc.first_node(), false);
}

xml_node<> *XmlParse::NodeFind(xml_document<> &doc, const std::string& NodeName, xml_node<> *CurNode)
{
	std::string curnodename =  CurNode->name();	
	if (NodeName == curnodename)
	{
		return CurNode;
	}
	//遍历孩子节点
	xml_node<> *childNode = CurNode->first_node();
	if (childNode)
	{
		xml_node<>  *FindNode ;		
		FindNode =  NodeFind(doc, NodeName, childNode);
		if (FindNode)
		{
			return FindNode;
		}
	}
	//遍历兄弟节点
	CurNode = CurNode->next_sibling();
	if (CurNode)
	{
		xml_node<>  *FindNode = NodeFind(doc, NodeName, CurNode);
		if (FindNode)
		{
			return  FindNode;
		}
	}
	// 	for (CurNode = CurNode->next_sibling(); CurNode; CurNode = CurNode->next_sibling())
	// 	{		
	// 		if (CurNode)
	// 		{
	// 			xml_node<>  *FindNode = NodeFind(doc, NodeName, CurNode);
	// 			if (FindNode)
	// 			{
	// 				return  FindNode;
	// 			}
	// 		}
	// 	}

	return NULL;
}

xml_node<>* XmlParse::NextNodeFind(xml_document<> &doc, xml_node<> *node, xml_node <> *CurNode, bool bSame)
{
	std::string curnodename =  CurNode->name();	
	if ((node->name() == curnodename) && bSame)
	{
		return CurNode;
	}
	if (node == CurNode)
	{
		bSame = true;
	}
	//遍历孩子节点
	xml_node<> *childNode = CurNode->first_node();
	if (childNode)
	{
		xml_node<>  *FindNode ;		
		FindNode =  NextNodeFind(doc, node, childNode, bSame);
		if (FindNode)
		{
			return FindNode;
		}
	}
	//遍历兄弟节点
	for (CurNode = CurNode->next_sibling(); CurNode; CurNode = CurNode->next_sibling())
	{		
		if (CurNode)
		{
			xml_node<>  *FindNode = NextNodeFind(doc, node, CurNode, bSame);
			if (FindNode)
			{
				return  FindNode;
			}
		}
	}

	return NULL;
}
