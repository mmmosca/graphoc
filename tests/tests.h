/**
 *  This program is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see https://www.gnu.org/licenses/.
 *  
 *  \brief  Test data
 *  \author Marco M. Mosca, email: marcomichele.mosca@gmail.com
 *
*/
#include <stdio.h>
#include <stdlib.h>

static char* labels[] = {
    "CAMBRIDGE",
    "LONDON",
    "MANCHESTER",
    "LIVERPOOL",
    "OXFORD",
    NULL,
};

static char* edges[] = {
    "CAMBRIDGE:LONDON:20.0",
    "CAMBRIDGE:MANCHESTER:40.0",
    "MANCHESTER:LIVERPOOL:20.0",
    "CAMBRIDGE:LIVERPOOL:60.0",
    "CAMBRIDGE:OXFORD:10.0",
    "OXFORD:LIVERPOOL:40.0",
    NULL,
};

static char* wrongedges[] = {
    "CAMBRIDGE:LONDON:UNKNOWN",
    "CAMBRIDGE:LONDON:",
    "CAMBRIDGE",
    NULL,
};

static int degrees[]= {
    4,
    0,
    1,
    0,
    1,
};

static unsigned int camb_distances[] = {
	0.0,
	20.0,
	40.0,
	50.0,
	10.0,
};
