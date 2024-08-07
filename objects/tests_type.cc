// SPDX-FileCopyrightText: 2004 Dominique Devriese <devriese@kde.org>

// SPDX-License-Identifier: GPL-2.0-or-later

#include "tests_type.h"

#include <math.h>

#include "bogus_imp.h"
#include "line_imp.h"
#include "other_imp.h"
#include "point_imp.h"
#include "polygon_imp.h"

#include <cmath>

static const ArgsParser::spec argsspecAreParallel[] = {
    {AbstractLineImp::stype(), kli18n("Is this line parallel?"), kli18n("Select the first of the two possibly parallel lines..."), false},
    {AbstractLineImp::stype(), kli18n("Parallel to this line?"), kli18n("Select the other of the two possibly parallel lines..."), false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(AreParallelType)

AreParallelType::AreParallelType()
    : ArgsParserObjectType("AreParallel", argsspecAreParallel, 2)
{
}

AreParallelType::~AreParallelType()
{
}

const AreParallelType *AreParallelType::instance()
{
    static const AreParallelType t;
    return &t;
}

ObjectImp *AreParallelType::calc(const Args &parents, const KigDocument &) const
{
    if (!margsparser.checkArgs(parents))
        return new InvalidImp;
    const LineData &l1 = static_cast<const AbstractLineImp *>(parents[0])->data();
    const LineData &l2 = static_cast<const AbstractLineImp *>(parents[1])->data();

    if (l1.isParallelTo(l2))
        return new TestResultImp(true, i18n("These lines are parallel."));
    else
        return new TestResultImp(false, i18n("These lines are not parallel."));
}

const ObjectImpType *AreParallelType::resultId() const
{
    return TestResultImp::stype();
}

static const ArgsParser::spec argsspecAreOrthogonal[] = {
    {AbstractLineImp::stype(), kli18n("Is this line orthogonal?"), kli18n("Select the first of the two possibly orthogonal lines..."), false},
    {AbstractLineImp::stype(), kli18n("Orthogonal to this line?"), kli18n("Select the other of the two possibly orthogonal lines..."), false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(AreOrthogonalType)

AreOrthogonalType::AreOrthogonalType()
    : ArgsParserObjectType("AreOrthogonal", argsspecAreOrthogonal, 2)
{
}

AreOrthogonalType::~AreOrthogonalType()
{
}

const AreOrthogonalType *AreOrthogonalType::instance()
{
    static const AreOrthogonalType t;
    return &t;
}

ObjectImp *AreOrthogonalType::calc(const Args &parents, const KigDocument &) const
{
    if (!margsparser.checkArgs(parents))
        return new InvalidImp;
    const LineData &l1 = static_cast<const AbstractLineImp *>(parents[0])->data();
    const LineData &l2 = static_cast<const AbstractLineImp *>(parents[1])->data();

    if (l1.isOrthogonalTo(l2))
        return new TestResultImp(true, i18n("These lines are orthogonal."));
    else
        return new TestResultImp(false, i18n("These lines are not orthogonal."));
}

const ObjectImpType *AreOrthogonalType::resultId() const
{
    return TestResultImp::stype();
}

static const ArgsParser::spec argsspecAreCollinear[] = {
    {PointImp::stype(), kli18n("Check collinearity of this point"), kli18n("Select the first of the three possibly collinear points..."), false},
    {PointImp::stype(), kli18n("and this second point"), kli18n("Select the second of the three possibly collinear points..."), false},
    {PointImp::stype(), kli18n("with this third point"), kli18n("Select the last of the three possibly collinear points..."), false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(AreCollinearType)

AreCollinearType::AreCollinearType()
    : ArgsParserObjectType("AreCollinear", argsspecAreCollinear, 3)
{
}

AreCollinearType::~AreCollinearType()
{
}

const AreCollinearType *AreCollinearType::instance()
{
    static const AreCollinearType t;
    return &t;
}

ObjectImp *AreCollinearType::calc(const Args &parents, const KigDocument &) const
{
    if (!margsparser.checkArgs(parents))
        return new InvalidImp;
    const Coordinate &p1 = static_cast<const PointImp *>(parents[0])->coordinate();
    const Coordinate &p2 = static_cast<const PointImp *>(parents[1])->coordinate();
    const Coordinate &p3 = static_cast<const PointImp *>(parents[2])->coordinate();

    if (areCollinear(p1, p2, p3))
        return new TestResultImp(true, i18n("These points are collinear."));
    else
        return new TestResultImp(false, i18n("These points are not collinear."));
}

const ObjectImpType *AreCollinearType::resultId() const
{
    return TestResultImp::stype();
}

static const ArgsParser::spec containsTestArgsSpec[] = {
    {PointImp::stype(), kli18n("Check whether this point is on a curve"), kli18n("Select the point you want to test..."), false},
    {CurveImp::stype(), kli18n("Check whether the point is on this curve"), kli18n("Select the curve that the point might be on..."), false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(ContainsTestType)

ContainsTestType::ContainsTestType()
    : ArgsParserObjectType("ContainsTest", containsTestArgsSpec, 2)
{
}

ContainsTestType::~ContainsTestType()
{
}

const ContainsTestType *ContainsTestType::instance()
{
    static const ContainsTestType t;
    return &t;
}

ObjectImp *ContainsTestType::calc(const Args &parents, const KigDocument &doc) const
{
    if (!margsparser.checkArgs(parents))
        return new InvalidImp;
    const Coordinate &p = static_cast<const PointImp *>(parents[0])->coordinate();
    const CurveImp *c = static_cast<const CurveImp *>(parents[1]);

    if (c->containsPoint(p, doc))
        return new TestResultImp(true, i18n("This curve contains the point."));
    else
        return new TestResultImp(false, i18n("This curve does not contain the point."));
}

const ObjectImpType *ContainsTestType::resultId() const
{
    return TestResultImp::stype();
}

/*
 * containment test of a point in a polygon
 */

static const ArgsParser::spec InPolygonTestArgsSpec[] = {
    {PointImp::stype(), kli18n("Check whether this point is in a polygon"), kli18n("Select the point you want to test..."), false},
    {FilledPolygonImp::stype(), kli18n("Check whether the point is in this polygon"), kli18n("Select the polygon that the point might be in..."), false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(InPolygonTestType)

InPolygonTestType::InPolygonTestType()
    : ArgsParserObjectType("InPolygonTest", InPolygonTestArgsSpec, 2)
{
}

InPolygonTestType::~InPolygonTestType()
{
}

const InPolygonTestType *InPolygonTestType::instance()
{
    static const InPolygonTestType t;
    return &t;
}

ObjectImp *InPolygonTestType::calc(const Args &parents, const KigDocument &) const
{
    if (!margsparser.checkArgs(parents))
        return new InvalidImp;
    const Coordinate &p = static_cast<const PointImp *>(parents[0])->coordinate();
    const FilledPolygonImp *pol = static_cast<const FilledPolygonImp *>(parents[1]);

    if (pol->isInPolygon(p))
        return new TestResultImp(true, i18n("This polygon contains the point."));
    else
        return new TestResultImp(false, i18n("This polygon does not contain the point."));
}

const ObjectImpType *InPolygonTestType::resultId() const
{
    return TestResultImp::stype();
}

/*
 * test if a polygon is convex
 */

static const ArgsParser::spec ConvexPolygonTestArgsSpec[] = {
    {FilledPolygonImp::stype(), kli18n("Check whether this polygon is convex"), kli18n("Select the polygon you want to test for convexity..."), false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(ConvexPolygonTestType)

ConvexPolygonTestType::ConvexPolygonTestType()
    : ArgsParserObjectType("ConvexPolygonTest", ConvexPolygonTestArgsSpec, 1)
{
}

ConvexPolygonTestType::~ConvexPolygonTestType()
{
}

const ConvexPolygonTestType *ConvexPolygonTestType::instance()
{
    static const ConvexPolygonTestType t;
    return &t;
}

ObjectImp *ConvexPolygonTestType::calc(const Args &parents, const KigDocument &) const
{
    if (!margsparser.checkArgs(parents))
        return new InvalidImp;
    const FilledPolygonImp *pol = static_cast<const FilledPolygonImp *>(parents[0]);

    if (pol->isConvex())
        return new TestResultImp(true, i18n("This polygon is convex."));
    else
        return new TestResultImp(false, i18n("This polygon is not convex."));
}

const ObjectImpType *ConvexPolygonTestType::resultId() const
{
    return TestResultImp::stype();
}

/*
 * same distance test
 */

static const ArgsParser::spec argsspecSameDistanceType[] = {
    {PointImp::stype(),
     kli18n("Check if this point has the same distance"),
     kli18n("Select the point which might have the same distance from two other points..."),
     false},
    {PointImp::stype(), kli18n("from this point"), kli18n("Select the first of the two other points..."), false},
    {PointImp::stype(), kli18n("and from this second point"), kli18n("Select the other of the two other points..."), false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(SameDistanceType)

SameDistanceType::SameDistanceType()
    : ArgsParserObjectType("SameDistanceType", argsspecSameDistanceType, 3)
{
}

SameDistanceType::~SameDistanceType()
{
}

const SameDistanceType *SameDistanceType::instance()
{
    static const SameDistanceType t;
    return &t;
}

ObjectImp *SameDistanceType::calc(const Args &parents, const KigDocument &) const
{
    if (!margsparser.checkArgs(parents))
        return new InvalidImp;
    const Coordinate &p1 = static_cast<const PointImp *>(parents[0])->coordinate();
    const Coordinate &p2 = static_cast<const PointImp *>(parents[1])->coordinate();
    const Coordinate &p3 = static_cast<const PointImp *>(parents[2])->coordinate();

    if (fabs((p1 - p2).length() - (p1 - p3).length()) < 10e-5)
        return new TestResultImp(true, i18n("The two distances are the same."));
    else
        return new TestResultImp(false, i18n("The two distances are not the same."));
}

const ObjectImpType *SameDistanceType::resultId() const
{
    return TestResultImp::stype();
}

static const ArgsParser::spec vectorEqualityArgsSpec[] = {{VectorImp::stype(),
                                                           kli18n("Check whether this vector is equal to another vector"),
                                                           kli18n("Select the first of the two possibly equal vectors..."),
                                                           false},
                                                          {VectorImp::stype(),
                                                           kli18n("Check whether this vector is equal to the other vector"),
                                                           kli18n("Select the other of the two possibly equal vectors..."),
                                                           false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(VectorEqualityTestType)

VectorEqualityTestType::VectorEqualityTestType()
    : ArgsParserObjectType("VectorEquality", vectorEqualityArgsSpec, 2)
{
}

VectorEqualityTestType::~VectorEqualityTestType()
{
}

const VectorEqualityTestType *VectorEqualityTestType::instance()
{
    static const VectorEqualityTestType t;
    return &t;
}

ObjectImp *VectorEqualityTestType::calc(const Args &parents, const KigDocument &) const
{
    if (!margsparser.checkArgs(parents))
        return new InvalidImp;
    const Coordinate &v1 = static_cast<const VectorImp *>(parents[0])->dir();
    const Coordinate &v2 = static_cast<const VectorImp *>(parents[1])->dir();

    if ((v1 - v2).length() < 10e-5)
        return new TestResultImp(true, i18n("The two vectors are the same."));
    else
        return new TestResultImp(false, i18n("The two vectors are not the same."));
}

const ObjectImpType *VectorEqualityTestType::resultId() const
{
    return TestResultImp::stype();
}

static const ArgsParser::spec existenceArgsSpec[] = {
    {ObjectImp::stype(), kli18n("Check whether this object exists"), kli18n("Select the object for the existence check..."), false}};

KIG_INSTANTIATE_OBJECT_TYPE_INSTANCE(ExistenceTestType)

ExistenceTestType::ExistenceTestType()
    : ArgsParserObjectType("Existence", existenceArgsSpec, 1)
{
}

ExistenceTestType::~ExistenceTestType()
{
}

const ExistenceTestType *ExistenceTestType::instance()
{
    static const ExistenceTestType t;
    return &t;
}

ObjectImp *ExistenceTestType::calc(const Args &parents, const KigDocument &) const
{
    // if ( ! margsparser.checkArgs( parents ) ) return new InvalidImp;
    if (static_cast<const ObjectImp *>(parents[0])->valid())
        return new TestResultImp(true, i18n("The object exists."));
    else
        return new TestResultImp(false, i18n("The object does not exist."));
}

const ObjectImpType *ExistenceTestType::resultId() const
{
    return TestResultImp::stype();
}
