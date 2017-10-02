/* -*- c++ -*-
 * Copyright (c) 2012-2017 by the GalSim developers team on GitHub
 * https://github.com/GalSim-developers
 *
 * This file is part of GalSim: The modular galaxy image simulation toolkit.
 * https://github.com/GalSim-developers/GalSim
 *
 * GalSim is free software: redistribution and use in source and binary forms,
 * with or without modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions, and the disclaimer given in the accompanying LICENSE
 *    file.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, and the disclaimer given in the documentation
 *    and/or other materials provided with the distribution.
 */

#include "galsim/IgnoreWarnings.h"
#include "boost/python.hpp"

#include "boost/python/stl_iterator.hpp"

#include "SBAdd.h"

namespace bp = boost::python;

namespace galsim {

    struct PySBAdd
    {
        // This will be wrapped as a Python constructor; it accepts an arbitrary Python iterable.
        static SBAdd* construct(const bp::object& iterable, GSParams gsparams)
        {
            bp::stl_input_iterator<SBProfile> begin(iterable), end;
            std::list<SBProfile> plist(begin, end);
            return new SBAdd(plist, gsparams);
        }

        static void wrap()
        {
            bp::class_< SBAdd, bp::bases<SBProfile> >("SBAdd", bp::no_init)
                // bp tries the overloads in reverse order, so we wrap the most general one first
                // to ensure we try it last
                .def("__init__", bp::make_constructor(
                        &construct, bp::default_call_policies(),
                        (bp::arg("slist"), bp::arg("gsparams"))));
        }
    };

    void pyExportSBAdd()
    {
        PySBAdd::wrap();
    }

} // namespace galsim
