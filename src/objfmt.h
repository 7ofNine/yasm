/* $IdPath$
 * Object format module interface header file
 *
 *  Copyright (C) 2001  Peter Johnson
 *
 *  This file is part of YASM.
 *
 *  YASM is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  YASM is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef YASM_OBJFMT_H
#define YASM_OBJFMT_H

/* Interface to the object format module(s) */
struct objfmt {
    /* one-line description of the format */
    const char *name;

    /* keyword used to select format on the command line */
    const char *keyword;

    /* default (starting) section name */
    const char *default_section_name;

    /* default (starting) BITS setting */
    const unsigned char default_mode_bits;

    /* NULL-terminated list of debugging formats that are valid to use with
     * this object format.
     */
/*    debugfmt **debugfmts;*/

    /* Default debugging format (set even if there's only one available to
     * use)
     */
/*    debugfmt *default_df;*/

    /* Switch object file sections.  The first val of the valparams should
     * be the section name.
     */
    /*@dependent@*/ /*@null@*/ section *
	(*sections_switch)(sectionhead *headp, valparamhead *valparams,
			   /*@null@*/ valparamhead *objext_valparams);

    void (*section_data_delete)(/*@only@*/ void *data);
    void (*section_data_print)(void *data);

    /*@null@*/ void *(*extern_data_new)(const char *name, /*@null@*/
					valparamhead *objext_valparams);
    /*@null@*/ void *(*global_data_new)(const char *name, /*@null@*/
					valparamhead *objext_valparams);
    /*@null@*/ void *(*common_data_new)(const char *name,
					/*@only@*/ expr *size, /*@null@*/
					valparamhead *objext_valparams);

    /* It's only valid to pass this *one* SymVisibility (eg, vis is an enum not
     * a bitmask).
     */
    void (*declare_data_delete)(SymVisibility vis, /*@only@*/ void *data);

    /* Object format-specific directive support.  Returns 1 if directive was
     * not recognized.  Returns 0 if directive was recognized, even if it
     * wasn't valid.
     */
    int (*directive)(const char *name, valparamhead *valparams,
		     /*@null@*/ valparamhead *objext_valparams);
};

/* Generic functions for all object formats - implemented in src/objfmt.c */

/* Finds an object format based on its keyword.  Returns NULL if no match was
 * found.
 */
/*@null@*/ objfmt *find_objfmt(const char *keyword);

/* Lists all available object formats.  Calls printfunc with the name and
 * keyword of each available format.
 */
void list_objfmts(void (*printfunc) (const char *name, const char *keyword));

#endif
