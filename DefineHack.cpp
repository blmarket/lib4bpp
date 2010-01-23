/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
//
// demo_xml.cpp
//
// (C) Copyright 2002-4 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

#include <cstdio> // remove
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::remove;
}
#endif

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "demo_gps.hpp"

using namespace std;

void save_schedule(const bus_schedule &s, const char * filename){
    // make an archive
    std::ofstream ofs(filename);
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(s);
}

void
restore_schedule(bus_schedule &s, const char * filename)
{
    // open the archive
    std::ifstream ifs(filename);
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);

    // restore the schedule from the archive
    ia >> BOOST_SERIALIZATION_NVP(s);
}

typedef std::map<int,string> map_type;

struct news
{
	news() {};
	news(int x,int y,int z) : x(x),y(y),z(z) {}
	int x,y,z;
};

struct asdf
{
	int a,b,c;
	map_type vv;
	news yy;
};

#define asdf_LIST() \
	DATA(int, a) \
	DATA(int, b) \
	DATA(int, c) \
	DATA(map_type, vv) \
	DATA(news, yy)

#define news_LIST() \
	DATA(int, x) \
	DATA(int, y) \
	DATA(int, z)

#define STRUCT_LIST() \
	STRUCT(asdf) \
	STRUCT(news)

BOOST_SERIALIZATION_SPLIT_FREE(map_type);

#define STRUCT(struct_type) BOOST_SERIALIZATION_SPLIT_FREE(struct_type);
STRUCT_LIST()
#undef STRUCT

namespace boost {
namespace serialization { 

#define DATA(type,value) ar & BOOST_SERIALIZATION_NVP(data.value);
#define STRUCT(struct_type) \
	template<class Archive> \
	void save(Archive &ar, const struct_type & data, const unsigned int version) \
	{ \
		struct_type##_LIST() \
	} 
STRUCT_LIST()
#undef STRUCT
#undef DATA

}
}

/*
template<class Archive>
void save(Archive &ar, const asdf &data, const unsigned int version)
{
#define DATA(type, value) ar & BOOST_SERIALIZATION_NVP(data.value);
	ASDF_LIST()
#undef DATA
}
*/

namespace boost { namespace serialization {

template<class Archive>
void save(Archive &ar, const map_type &data, const unsigned int version)
{
	for(map_type::const_iterator iter = data.begin(); iter != data.end(); ++iter)
	{
		ar & boost::serialization::nvp<pair<int,string> >("data", make_pair(iter->first, iter->second) );
	}
}

}}

int main(void)
{
	std::ostringstream ost;
	boost::archive::xml_oarchive oa(ost);
	asdf tmp;
	tmp.a=tmp.b=tmp.c=123;
	tmp.vv[5] = "asdf";
	tmp.yy = news(3,5,8);
	oa << BOOST_SERIALIZATION_NVP(tmp);
	std::cout << ost.str() << std::endl;
}

/*
int main(int argc, char *argv[])
{   
    // make the schedule
    bus_schedule original_schedule;

    // fill in the data
    // make a few stops
    bus_stop *bs0 = new bus_stop_corner(
        gps_position(34, 135, 52.560f),
        gps_position(134, 22, 78.30f),
        "24th Street", "10th Avenue"
    );
    bus_stop *bs1 = new bus_stop_corner(
        gps_position(35, 137, 23.456f),
        gps_position(133, 35, 54.12f),
        "State street", "Cathedral Vista Lane"
    );
    bus_stop *bs2 = new bus_stop_destination(
        gps_position(35, 136, 15.456f),
        gps_position(133, 32, 15.300f),
        "White House"
    );
    bus_stop *bs3 = new bus_stop_destination(
        gps_position(35, 134, 48.789f),
        gps_position(133, 32, 16.230f),
        "Lincoln Memorial"
    );

    // make a  routes
    bus_route route0;
    route0.append(bs0);
    route0.append(bs1);
    route0.append(bs2);

    // add trips to schedule
    original_schedule.append("bob", 6, 24, &route0);
    original_schedule.append("bob", 9, 57, &route0);
    original_schedule.append("alice", 11, 02, &route0);

    // make aother routes
    bus_route route1;
    route1.append(bs3);
    route1.append(bs2);
    route1.append(bs1);

    // add trips to schedule
    original_schedule.append("ted", 7, 17, &route1);
    original_schedule.append("ted", 9, 38, &route1);
    original_schedule.append("alice", 11, 47, &route1);

    // display the complete schedule
    std::cout << "original schedule";
    std::cout << original_schedule;
    
    std::string filename(boost::archive::tmpdir());
    filename += "/demo.xml";

    // save the schedule
    save_schedule(original_schedule, filename.c_str());

    // ... some time later
    // make  a new schedule
    bus_schedule new_schedule;

    restore_schedule(new_schedule, filename.c_str());

    // and display
    std::cout << "\nrestored schedule";
    std::cout << new_schedule;
    // should be the same as the old one. (except for the pointer values)

    std::remove(filename.c_str());

    delete bs0;
    delete bs1;
    delete bs2;
    delete bs3;
    return 0;
}
*/