/**********************************
 * File: XmlParse.hpp
 * Author: ponlee
 * Version: 1.0
 * Date: 2014-04
 * Desc: xml文件工具类
 * Remark：依赖第三方库：RapidXml
***********************************/

#ifndef _XML_PARSE_HPP__
#define _XML_PARSE_HPP__

#include <string>
#include <cstdio>
#include <assert.h>

#include "rapidxml/rapidxml.hpp"

class XmlParse
{
private:
	typedef XmlParse						this_type;

public:
	static void InitXml(rapidxml::xml_document<> &doc);

	static rapidxml::xml_node<> *AppendNode(const std::string &NewNodeName, const std::string &NewNodeValue,
		rapidxml::xml_document<> &doc, rapidxml::xml_node<> *ParentNode);

	static void AppendAttribute(const std::string &NewAttributeName, const std::string& NewAttributeValue
		,rapidxml::xml_document<> &doc, rapidxml::xml_node<> *ParentNode);

	/**
	* FUNC: 得到指定类型的属性
	**/
	template<typename _Type>
	static _Type GetXmlAttribute(const std::string& attributeName,rapidxml::xml_node<>* node,bool isThrow = true);

	static std::string GetXmlAttribute(const std::string& attributeName, rapidxml::xml_node<> *Node,bool isThrow = true);

	static rapidxml::xml_node<> *FindFirstNode(rapidxml::xml_document<> &doc, std::string NodeName);
	static rapidxml::xml_node<> *FindNextSameValueNode(rapidxml::xml_document<> &doc, rapidxml::xml_node<> *CurNode);

	static std::string Gbk2Utf(const std::string &xml);
	static std::string Utf2Gbk(const std::string &xml);

private:
	static rapidxml::xml_node<> *NodeFind(rapidxml::xml_document<> &doc, const std::string& NodeName, rapidxml::xml_node<> *CurNode);
	static rapidxml::xml_node<> *NextNodeFind(rapidxml::xml_document<> &doc, rapidxml::xml_node<> *node, rapidxml::xml_node <> *CurNode, bool isSame = false);

	static std::string GetXmlAttributeImpl(const std::string& attributeName, rapidxml::xml_node<> *Node, bool isThrow = true);
};

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename _Type>
_Type XmlParse::GetXmlAttribute(const std::string& attributeName,rapidxml::xml_node<>* node,bool isThrow)
{
	std::string result = GetXmlAttributeImpl(attributeName, node, isThrow);	
	//TODO: 将字符串转化为模板指定类型（_Type）
	return result;
}

#endif
