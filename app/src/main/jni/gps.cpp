#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <android/log.h>

#include "gps.hpp"

const char *FILENAME = "gps.dat";

std::ostream &operator<<(std::ostream &s, gps_position const &g)
{
    s << "GPS(" << g.degrees << "/" << g.minutes << "/" << g.seconds << ")";
    return s;
}

void save(std::string const &root, gps_position const &g)
{
    // create and open a character archive for output
    std::ofstream ofs(root + "/" + FILENAME);
    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << g;
    // archive and stream closed when destructors are called
    boost::shared_ptr<boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend>> file_sink;
    file_sink = boost::log::add_file_log("/data/data/net.crystax.testboost2/files/sample.log");
    BOOST_LOG_TRIVIAL(trace) << "a trace message";
}

void load(std::string const &root, gps_position &g)
{
    // create and open an archive for input
    std::ifstream ifs(root + "/" + FILENAME);
    boost::filesystem::path tmp = "/root";
    boost::filesystem::path fname = "filename";
    tmp /= fname;
    __android_log_print(ANDROID_LOG_INFO, "The boost::filesystem::path tmp is %s.", tmp.string().c_str());
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> g;
    // archive and stream closed when destructors are called
}
