//==========================================================
//NamedProperties.hpp
//==========================================================
#pragma once
#ifndef _NAMEDPROPERTIES_HPP_
#define _NAMEDPROPERTIES_HPP_

#include <string>
#include <map>

enum PropertyGetResult
{
	RESULT_SUCCESS,
	RESULT_FAILED_NO_SUCH_PROPERTY,
	RESULT_FAILED_WRONG_TYPE,
	RESULT_PROPERTIES_WAS_EMPTY,
	NUM_OF_RESULT,
};

class TypedPropertyBase
{
public:
	virtual bool IsOfType(const type_info& compareType) = 0;
	virtual TypedPropertyBase* MakeACopy() = 0;
};
//////////////////////////////////////////////////////////////////////////
template<typename T_PropertyType>
class TypedProperty : public TypedPropertyBase
{
public:
	// const char* GetTypeName() const;
	T_PropertyType m_propertyValue;

	TypedProperty<T_PropertyType>(const T_PropertyType& properityValue)
		:m_propertyValue(properityValue)
	{}
	virtual bool IsOfType(const type_info& compareType)
	{
		const type_info& myType = typeid(T_PropertyType);
		return (myType == compareType);
	}

	virtual TypedPropertyBase* MakeACopy()
	{
		TypedProperty<T_PropertyType>* newOne = new TypedProperty<T_PropertyType>(m_propertyValue);
		return newOne;
	}
};
//////////////////////////////////////////////////////////////////////////
class NamedProperties
{
public:
	std::map<std::string, TypedPropertyBase*> m_properties;
//public:
	NamedProperties(NamedProperties& copy);
	NamedProperties() {};
	template<typename T>
	void Set( const std::string& properityName, const T& value );
	template<typename T1,typename T2>
	void Set(const std::string& properityName1, const T1& value1, const std::string& properityName2, const T2& value2);
	template<typename T1, typename T2,typename T3>
	void Set(const std::string& properityName1, const T1& value1, const std::string& properityName2, const T2& value2, const std::string& properityName3, const T3& value3);
	void Set(const std::string& properityName, const char* value);
	template<typename T>
	PropertyGetResult Get(const std::string& propertyName, T& out_propertyValue) const;
	PropertyGetResult Get(const std::string& propertyName, std::string& out_propertyValue) const;
	unsigned int GetPropertiesSize() { return m_properties.size(); }
};

template<typename T>
inline void NamedProperties::Set(const std::string& properityName, const T& value)
{
	auto found = m_properties.find(properityName);
	if (found != m_properties.end())
	{
		TypedPropertyBase* propertiesBase = found->second;
		if (propertiesBase->IsOfType(typeid(T)))
		{
			TypedProperty<T>* property = reinterpret_cast<TypedProperty<T>*>(propertiesBase);
			property->m_propertyValue = value;
			return;
		}
		else
		{
			m_properties.erase(found);
		}
	}

	TypedPropertyBase* newProperty = new TypedProperty<T>(value);
	m_properties[properityName] = newProperty;
}

template<typename T1, typename T2>
void NamedProperties::Set(const std::string& properityName1, const T1& value1, const std::string& properityName2, const T2& value2)
{
	Set(properityName1, value1);
	Set(properityName2, value2);
}

template<typename T1, typename T2, typename T3>
void NamedProperties::Set(const std::string& properityName1, const T1& value1, const std::string& properityName2, const T2& value2, const std::string& properityName3, const T3& value3)
{
	Set(properityName1, value1);
	Set(properityName2, value2);
	Set(properityName3, value3);
}

///----------------------------------------------------------
///
///----------------------------------------------------------

template<typename T>
inline PropertyGetResult NamedProperties::Get(const std::string& propertyName, T& out_propertyValue) const
{
	if (m_properties.empty())
	{
		return RESULT_PROPERTIES_WAS_EMPTY;
	}
	auto found = m_properties.find(propertyName);
	if (found == m_properties.end())
	{
		return RESULT_FAILED_NO_SUCH_PROPERTY;
	}
	TypedPropertyBase* property = found->second;
	if (property->IsOfType(typeid(T)))
	{
		TypedProperty<T>* typedProperty = reinterpret_cast<TypedProperty<T>*>(property);
		out_propertyValue = typedProperty->m_propertyValue;
		return RESULT_SUCCESS;
	}
	return RESULT_FAILED_WRONG_TYPE;
}
///----------------------------------------------------------
///
///----------------------------------------------------------


#endif