/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2013 NBEE Embedded Systems SL, Miguel Angel Ajo <miguelangel@ajo.es>
 * Copyright (C) 2013 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */


/**
 * @file  footprint_wizard.h
 * @brief Class FOOTPRINT_WIZARD and FOOTPRINT_WIZARDS
 */

#ifndef FOOTPRINT_WIZARD_H
#define FOOTPRINT_WIZARD_H

#include <vector>
#include <pcb_edit_frame.h>

// Allowable parameter types for PCB wizards
const wxString WIZARD_PARAM_UNITS_MM        = "mm";          // Millimetres
const wxString WIZARD_PARAM_UNITS_MILS      = "mils";        // Mils / thou
const wxString WIZARD_PARAM_UNITS_FLOAT     = "float";       // Floating point (dimensionless)
const wxString WIZARD_PARAM_UNITS_INTEGER   = "integer";     // Integer (dimensionless)
const wxString WIZARD_PARAM_UNITS_BOOL      = "bool";        // Boolean option
const wxString WIZARD_PARAM_UNITS_RADIANS   = "radians";     // Angle (radians)
const wxString WIZARD_PARAM_UNITS_DEGREES   = "degrees";     // Angle (degrees)
const wxString WIZARD_PARAM_UNITS_PERCENT   = "%";           // Percent (0% -> 100%)
const wxString WIZARD_PARAM_UNITS_STRING    = "string";      // String

/**
 * FOOTPRINT_WIZARD
 * This is the parent class from where any footprint wizard class must
 * derive */
class FOOTPRINT_WIZARD
{
public:
    FOOTPRINT_WIZARD() {}
    virtual ~FOOTPRINT_WIZARD();

    /**
     * Function GetName
     * @return the name of the wizard
     */
    virtual wxString        GetName() = 0;

    /**
     * Function GetImage
     * @return an svg image of the wizard to be rendered
     */
    virtual wxString        GetImage() = 0;

    /**
     * Function GetDescription
     * @return a description of the footprint wizard
     */
    virtual wxString        GetDescription() = 0;

    /**
     * Function GetNumParameterPages
     * @return the number of parameter pages that this wizard will show to the user
     */
    virtual int             GetNumParameterPages() = 0;

    /**
     * Function GetParameterPageName
     * @param aPage is the page we want the name of
     * @return a string with the page name
     */
    virtual wxString        GetParameterPageName( int aPage ) = 0;

    /**
     * Function GetParameterNames
     * @param aPage is the page we want the parameter names of
     * @return an array string with the parameter names on a certain page
     */
    virtual wxArrayString   GetParameterNames( int aPage ) = 0;

    /**
     * Function GetParameterTypes
     * @param aPage is the page we want the parameter types of
     * @return an array string with the parameter types on a certain page
     *          "IU" for internal units, "UNITS" for units (0,1,2,3...,N)
     */
    virtual wxArrayString   GetParameterTypes( int aPage ) = 0;


    /**
     * Function GetParameterValues
     * @param aPage is the page we want the parameter values of
     * @return an array of parameter values
     */
    virtual wxArrayString   GetParameterValues( int aPage ) = 0;

    /**
     * Function GetParameterErrors
     * @param aPage is the page we want to know the errors of
     * @return an array of errors (if any) for the parameters, empty strings for OK parameters
     */
    virtual wxArrayString   GetParameterErrors( int aPage ) = 0;

    /**
     * Function GetParameterHints
     * @param aPage is the page we want to know the hints of
     * @return an array of hints (if any) for the parameters, empty string for no hints
     */
    virtual wxArrayString   GetParameterHints( int aPage ) = 0;

    /**
     * Function GetParamaterDesignators
     * @param aPage is the page we want to know the designators of
     * @return an array of designators (blank strings for no designators
     */
    virtual wxArrayString    GetParameterDesignators( int aPage ) = 0;

    /**
     * Function SetParameterValues
     * @param aPage is the page we want to set the parameters in
     * @param aValues are the values we want to set into the parameters
     * @return an array of parameter values
     */
    virtual wxString        SetParameterValues( int aPage, wxArrayString& aValues ) = 0;

    /**
     * Function ResetParameters
     * Reset all wizard parameters to default values
     */
    virtual void ResetParameters() = 0;

    /**
     * Function GetModule
     * This method builds the module itself and returns it to the caller function
     * @return  PCB module built from the parameters given to the class
     * @param aMessage a wxString to store messages (if any) generated by the
     * footprint generator
     */
    virtual MODULE*         GetFootprint( wxString* aMessage ) = 0;

    /**
     * Function GetObject
     * This method gets the pointer to the object from where this wizard constructs
     * @return  it's a void pointer, as it could be a PyObject or any other
     */
    virtual void*           GetObject() = 0;

    /**
     * Function register_wizard
     * It's the standard method of a "FOOTPRINT_WIZARD" to register itself into
     * the FOOTPRINT_WIZARD_LIST singleton manager
     */
    void                    register_wizard();
};


class FOOTPRINT_WIZARD_LIST
{
private:
    /**
     * FOOTPRINT_WIZARD system wide static list
     */
    static std::vector<FOOTPRINT_WIZARD*> m_FootprintWizards;

public:

    /**
     * Function register_wizard
     * A footprint wizard calls this static method when it wants to register itself
     * into the system wizards
     * Note: if it is already registered, this function do nothing
     * if n existing wizard with the same name exists, this existing wizard will be
     * unregistered.
     * @param aWizard is the footprint wizard to be registered
     */
    static void                 register_wizard( FOOTPRINT_WIZARD* aWizard );

    /**
     * Function deregister_object
     * Anyone calls this method to deregister an object which builds a wizard,
     * it will lookup on the vector calling GetObject until find, then removed
     * and deleted
     *
     * @param aObject is the footprint wizard object to be deregistered
     */
    static bool                 deregister_object( void* aObject );

    /**
     * Function GetWizard
     * @param aName is the footprint wizard name
     * @return a wizard object by it's name or NULL if it isn't available.
     */
    static FOOTPRINT_WIZARD*    GetWizard( const wxString& aName );

    /**
     * Function GetWizard
     * @return a wizard object by it's number or NULL if it isn't available.
     * @param  aIndex is the wizard index in list
     */
    static FOOTPRINT_WIZARD*    GetWizard( int aIndex );

    /**
     * Function GetWizardsCount
     * @return the number of wizards available into the system
     */
    static int                  GetWizardsCount();
};

#endif /* PCBNEW_FOOTPRINT_WIZARDS_H */
