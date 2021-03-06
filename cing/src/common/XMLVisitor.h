/*
  This source file is part of the Cing project
  For the latest info, see http://www.cing.cc

Copyright (c) 2008-2009 Julio Obelleiro and Jorge Cano

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _XMLVisitor_H_
#define _XMLVisitor_H_

// Precompiled headers
#include "Cing-Precompiled.h"


#include "CommonPrereqs.h"
#include "XMLElement.h"
#include "TinyXML/include/tinyxml.h"


namespace Cing
{

/**
 * Class used to walk through the xml nodes of an XMLElement (comes from TinyXML)
 */
  class XMLVisitor: public TiXmlVisitor
  {
  public:
    XMLVisitor( XMLElement::XMLDocSharedPtr& xmlDoc, const TiXmlElement& root , XMLElement::XMLElementArray& children, const String& path = "NO_PATH" );
    virtual ~XMLVisitor() {}

    /// Visit an element.
    virtual bool VisitEnter( const TiXmlElement& element, const TiXmlAttribute* firstAttribute );

    // Attributes
    XMLElement::XMLDocSharedPtr&	m_xmlDoc;
    XMLElement::XMLElementArray&	m_children;
    const String&					m_path;
	const TiXmlElement&				m_root; /// < Root node of the tree to visit (used because TinyXml also walks the visitor through the first node, the parent)
    std::vector< std::string >		m_tokens;
  };

} // namespace Cing

#endif // _XMLVisitor_H_