namespace ng = nigmoo; // redacted

template <typename T>
bool surfaceNormal2RotationFrame(
        ng::ISOPose3D<T> &out, const ng::Vector3D<T> &point, const ng::Vector3D<T> &normal, T tolerance = ng::Defaults<T>::getTolerance()
    )
{
    /// 1) If its null then this all blows up spectacularly
    if(ng::almostEqual(normal,ng::Vector3D<T>::NullVector))
    {
        return false; /// BYPASS, nope nope nope!
    }

    /// 2) Let w = normal and also let ZZ = w: we interpret the surface normal as its frame's Z normal
    ///
    ///    If we map w to a skew symmetric matrix called W and we have an arbitrary vector v,
    ///    W is a linear map such that W*v == w cross v. (W is the angular velocity matrix for rotation in the plane orthogonal to w)
    ///
    ///    |  0     -w(3)    w(2) |    | v(1) |     | w(2)*v(3) - w(3)*v(2) |
    ///    |  w(3)   0      -w(1) |  * | v(2) |  =  | w(3)*v(1) - w(1)*v(3) |
    ///    | -w(2)   w(1)    0    |    | v(3) |     | w(1)*v(2) - w(2)*v(1) |
    ///
    ///    Ergo, W*w == w cross w == 0. Since W is a linear map, it follows from its structure that it can be interpreted
    ///    as a set of 3 base vectors that an input vector is projected onto (matrix multiplication dots each row with the vector)
    ///    and W*w == 0, so generating W will create 3 vectors orthogonal to w!
    ///
    ///    One row/column may be all zero (results from w being one of the x/y/z unit vectors), however, and although
    ///    the null vector is technically orthogonal to every vector, we certainly can't use that to specify a frame vector!
    ///    Thus, we simply choose the first non-zero row/column of W and call it XX, then cross w with XX to get YY.
    ///    As long as we made the rows/columns of W from a unit vector this will work every time!

    auto ww( ng::getNormalized(normal) ); // leave mutable to modify in-place if row selection fails
    
    ng::Vector3D<T> xx(0, -ww.z(), ww.y()); // choose row 1...
    if(ng::almostEqual(xx,ng::Vector3D<T>::NullVector)) // failed on first try
    {
        // change from row 1 -> row 2 in place
        xx.x() = ww.z();
        xx.y() = 0;
        xx.z() = -ww.x();

        if(ng::almostEqual(xx,ng::Vector3D<T>::NullVector)) // failed on second try, this one will succeed!
        {
            // change from row 2 -> row 3 in place
            xx.x() = -ww.y();
            xx.y() = ww.x();
            xx.z() = 0;
        }
    } // end XX selection

    xx.normalize(); /// BK: IMPORTANT: failing to normalize this can bogus the entire result!

    // now we have unit z and unit x, obtaining y is trivial! box it all into an ISOPose...
    ng::convertHTransform3DToPose3D(
            ng::HTransform3D<T>( ng::RMatrix3D<T>(xx,ng::cross(ww,xx),ww), point ), 
            out
    );
    
    return true; /// EMBEDDED SUCCESS CASE
}