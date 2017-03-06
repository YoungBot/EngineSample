//==========================================================
//NamedProperties.cpp
//==========================================================

#include "NamedProperties.hpp"

void NamedProperties::Set(const std::string& properityName, const char* value)
{
	auto found = m_properties.find(properityName);
	if (found != m_properties.end())
	{
		TypedPropertyBase* propertiesBase = found->second;
		if (propertiesBase->IsOfType(typeid(const char*)))
		{
			TypedProperty<const char*>* property = reinterpret_cast<TypedProperty<const char*>*>(propertiesBase);
			property->m_propertyValue = value;
			return;
		}
		else
		{
			m_properties.erase(found);
		}
	}

	TypedPropertyBase* newProperty = new TypedProperty<const char*>(value);
	m_properties[properityName] = newProperty;
}

///----------------------------------------------------------
///
///----------------------------------------------------------
PropertyGetResult NamedProperties::Get(const std::string& propertyName, std::string& out_propertyValue) const
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
	if (property->IsOfType(typeid(std::string)))
	{
		TypedProperty<std::string>* typedProperty = reinterpret_cast<TypedProperty<std::string>*>(property);
		out_propertyValue = typedProperty->m_propertyValue;
		return RESULT_SUCCESS;
	}
	else if (property->IsOfType(typeid(const char*)))
	{
		TypedProperty<const char*>* typedProperty = reinterpret_cast<TypedProperty<const char*>*>(property);
		out_propertyValue = typedProperty->m_propertyValue;
		return RESULT_SUCCESS;
	}

	return RESULT_FAILED_WRONG_TYPE;
}

///----------------------------------------------------------
///
///----------------------------------------------------------
NamedProperties::NamedProperties(NamedProperties& copy)
{
	for (std::map<std::string, TypedPropertyBase*>::iterator currentIter = copy.m_properties.begin(); currentIter!= copy.m_properties.end(); ++currentIter)
	{
		m_properties[currentIter->first] = (*currentIter->second).MakeACopy();
	}
}

