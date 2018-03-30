/*
 * Copyright (C) 2018  Christian Berger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "catch.hpp"

#include "cluon/FromJSONVisitor.hpp"
#include "cluon/ToJSONVisitor.hpp"
#include "cluon/cluon.hpp"
#include "cluon/cluonDataStructures.hpp"
#include "cluon/cluonTestDataStructures.hpp"

#include <sstream>
#include <string>

TEST_CASE("Testing TimeStamp-1.") {
    cluon::data::TimeStamp ts1;
    REQUIRE(ts1.seconds() == 0);
    REQUIRE(ts1.microseconds() == 0);

    ts1.seconds(123).microseconds(456);

    cluon::ToJSONVisitor jsonEncoder;
    ts1.accept(jsonEncoder);

    const char *JSON = R"({"seconds":123,
"microseconds":456})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    cluon::data::TimeStamp ts2;
    REQUIRE(ts2.seconds() == 0);
    REQUIRE(ts2.microseconds() == 0);

    ts2.accept(jsonDecoder);

    REQUIRE(ts2.seconds() == ts1.seconds());
    REQUIRE(ts2.microseconds() == ts1.microseconds());
}

TEST_CASE("Testing TimeStamp-2.") {
    cluon::data::TimeStamp ts1;
    REQUIRE(ts1.seconds() == 0);
    REQUIRE(ts1.microseconds() == 0);

    ts1.seconds(123).microseconds(121);

    cluon::ToJSONVisitor jsonEncoder;
    ts1.accept(jsonEncoder);

    const char *JSON = R"({"seconds":123,
"microseconds":121})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    cluon::data::TimeStamp ts2;
    REQUIRE(ts2.seconds() == 0);
    REQUIRE(ts2.microseconds() == 0);

    ts2.accept(jsonDecoder);

    REQUIRE(ts2.seconds() == ts1.seconds());
    REQUIRE(ts2.microseconds() == ts1.microseconds());
}

TEST_CASE("Testing TimeStamp-3.") {
    cluon::data::TimeStamp ts1;
    REQUIRE(ts1.seconds() == 0);
    REQUIRE(ts1.microseconds() == 0);

    ts1.seconds(123).microseconds(65321);

    cluon::ToJSONVisitor jsonEncoder;
    ts1.accept(jsonEncoder);

    const char *JSON = R"({"seconds":123,
"microseconds":65321})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    cluon::data::TimeStamp ts2;
    REQUIRE(ts2.seconds() == 0);
    REQUIRE(ts2.microseconds() == 0);

    ts2.accept(jsonDecoder);

    REQUIRE(ts2.seconds() == ts1.seconds());
    REQUIRE(ts2.microseconds() == ts1.microseconds());
}

TEST_CASE("Testing MyTestMessage0.") {
    testdata::MyTestMessage0 tmp;
    REQUIRE(tmp.attribute1());
    REQUIRE('c' == tmp.attribute2());

    tmp.attribute2('d');

    cluon::ToJSONVisitor jsonEncoder;
    tmp.accept(jsonEncoder);

    const char *JSON = R"({"attribute1":1,
"attribute2":"d"})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    testdata::MyTestMessage0 tmp2;
    REQUIRE(tmp2.attribute1());
    REQUIRE('c' == tmp2.attribute2());

    tmp2.accept(jsonDecoder);

    REQUIRE(tmp2.attribute1() == tmp.attribute1());
    REQUIRE(tmp2.attribute2() == tmp.attribute2());
}

TEST_CASE("Testing MyTestMessage0 with false value.") {
    testdata::MyTestMessage0 tmp;
    REQUIRE(tmp.attribute1());
    REQUIRE('c' == tmp.attribute2());

    tmp.attribute1(false).attribute2('d');

    cluon::ToJSONVisitor jsonEncoder;
    tmp.accept(jsonEncoder);

    const char *JSON = R"({"attribute1":0,
"attribute2":"d"})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    testdata::MyTestMessage0 tmp2;
    REQUIRE(tmp2.attribute1());
    REQUIRE('c' == tmp2.attribute2());

    tmp2.accept(jsonDecoder);

    REQUIRE(tmp2.attribute1() == tmp.attribute1());
    REQUIRE(tmp2.attribute2() == tmp.attribute2());
}

TEST_CASE("Testing MyTestMessage9.") {
    testdata::MyTestMessage9 tmp;

    tmp.attribute1(1.1f);
    tmp.attribute2(1.23456789);
    REQUIRE(1.1f == Approx(tmp.attribute1()));
    REQUIRE(1.23456789 == Approx(tmp.attribute2()));

    cluon::ToJSONVisitor jsonEncoder;
    tmp.accept(jsonEncoder);

    const char *JSON = R"({"attribute1":1.1,
"attribute2":1.23456789})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    testdata::MyTestMessage9 tmp2;
    tmp2.accept(jsonDecoder);

    REQUIRE(1.1f == Approx(tmp2.attribute1()));
    REQUIRE(1.23456789 == Approx(tmp2.attribute2()));
}

TEST_CASE("Testing MyTestMessage3.") {
    testdata::MyTestMessage3 tmp;
    REQUIRE(124 == tmp.attribute1());
    REQUIRE(-124 == tmp.attribute2());

    tmp.attribute1(123).attribute2(-123);
    REQUIRE(123 == tmp.attribute1());
    REQUIRE(-123 == tmp.attribute2());

    cluon::ToJSONVisitor jsonEncoder;
    tmp.accept(jsonEncoder);

    const char *JSON = R"({"attribute1":123,
"attribute2":-123})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    testdata::MyTestMessage3 tmp2;
    REQUIRE(124 == tmp2.attribute1());
    REQUIRE(-124 == tmp2.attribute2());

    tmp2.accept(jsonDecoder);

    REQUIRE(tmp2.attribute1() == tmp.attribute1());
    REQUIRE(tmp2.attribute2() == tmp.attribute2());
}

TEST_CASE("Testing MyTestMessage4.") {
    testdata::MyTestMessage4 tmp;
    REQUIRE(tmp.attribute1().empty());

    tmp.attribute1("testing");
    REQUIRE("testing" == tmp.attribute1());

    cluon::ToJSONVisitor jsonEncoder;
    tmp.accept(jsonEncoder);

    const char *JSON = R"({"attribute1":"dGVzdGluZw=="})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    testdata::MyTestMessage4 tmp2;
    REQUIRE(tmp2.attribute1().empty());

    tmp2.accept(jsonDecoder);

    REQUIRE("testing" == tmp2.attribute1());
}

TEST_CASE("Testing MyTestMessage5.") {
    testdata::MyTestMessage5 tmp;

    REQUIRE(1 == tmp.attribute1());
    REQUIRE(-1 == tmp.attribute2());
    REQUIRE(100 == tmp.attribute3());
    REQUIRE(-100 == tmp.attribute4());
    REQUIRE(10000 == tmp.attribute5());
    REQUIRE(-10000 == tmp.attribute6());
    REQUIRE(12345 == tmp.attribute7());
    REQUIRE(-12345 == tmp.attribute8());
    REQUIRE(-1.2345f == Approx(tmp.attribute9()));
    REQUIRE(-10.2345 == Approx(tmp.attribute10()));
    REQUIRE("Hello World!" == tmp.attribute11());

    tmp.attribute1(3)
        .attribute2(-3)
        .attribute3(103)
        .attribute4(-103)
        .attribute5(10003)
        .attribute6(-10003)
        .attribute7(54321)
        .attribute8(-74321)
        .attribute9(-5.4321f)
        .attribute10(-50.4321)
        .attribute11("Hello cluon World!");

    REQUIRE(3 == tmp.attribute1());
    REQUIRE(-3 == tmp.attribute2());
    REQUIRE(103 == tmp.attribute3());
    REQUIRE(-103 == tmp.attribute4());
    REQUIRE(10003 == tmp.attribute5());
    REQUIRE(-10003 == tmp.attribute6());
    REQUIRE(54321 == tmp.attribute7());
    REQUIRE(-74321 == tmp.attribute8());
    REQUIRE(-5.4321f == Approx(tmp.attribute9()));
    REQUIRE(-50.4321 == Approx(tmp.attribute10()));
    REQUIRE("Hello cluon World!" == tmp.attribute11());

    cluon::ToJSONVisitor jsonEncoder;
    tmp.accept(jsonEncoder);

    const char *JSON = R"({"attribute1":3,
"attribute2":-3,
"attribute3":103,
"attribute4":-103,
"attribute5":10003,
"attribute6":-10003,
"attribute7":54321,
"attribute8":-74321,
"attribute9":-5.4321,
"attribute10":-50.4321,
"attribute11":"SGVsbG8gY2x1b24gV29ybGQh"})";

    REQUIRE(std::string(JSON) == jsonEncoder.json());

    std::stringstream sstr{jsonEncoder.json()};

    cluon::FromJSONVisitor jsonDecoder;
    jsonDecoder.decodeFrom(sstr);

    testdata::MyTestMessage5 tmp2;
    REQUIRE(1 == tmp2.attribute1());
    REQUIRE(-1 == tmp2.attribute2());
    REQUIRE(100 == tmp2.attribute3());
    REQUIRE(-100 == tmp2.attribute4());
    REQUIRE(10000 == tmp2.attribute5());
    REQUIRE(-10000 == tmp2.attribute6());
    REQUIRE(12345 == tmp2.attribute7());
    REQUIRE(-12345 == tmp2.attribute8());
    REQUIRE(-1.2345f == Approx(tmp2.attribute9()));
    REQUIRE(-10.2345 == Approx(tmp2.attribute10()));
    REQUIRE("Hello World!" == tmp2.attribute11());

    tmp2.accept(jsonDecoder);

    REQUIRE(tmp2.attribute1() == tmp.attribute1());
    REQUIRE(tmp2.attribute2() == tmp.attribute2());
    REQUIRE(tmp2.attribute3() == tmp.attribute3());
    REQUIRE(tmp2.attribute4() == tmp.attribute4());
    REQUIRE(tmp2.attribute5() == tmp.attribute5());
    REQUIRE(tmp2.attribute6() == tmp.attribute6());
    REQUIRE(tmp2.attribute7() == tmp.attribute7());
    REQUIRE(tmp2.attribute8() == tmp.attribute8());
    REQUIRE(tmp2.attribute9() == Approx(tmp.attribute9()));
    REQUIRE(tmp2.attribute10() == Approx(tmp.attribute10()));
    REQUIRE(tmp2.attribute11() == tmp.attribute11());
}

