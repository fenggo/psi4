#ifndef _psi_src_lib_libmints_moindexspace_h_
#define _psi_src_lib_libmints_moindexspace_h_

#include <string>

namespace boost {
template<class T>
class shared_ptr;
}

namespace psi {

class Matrix;
class IntegralFactory;
class Vector;
class Dimension;
class BasisSet;

class MOIndexSpace
{
    /// Number of irreps.
    int nirrep_;

    /// Name of the orbital space.
    std::string name_;

    /// AO->MO transformation matrix (ao x mo)
    boost::shared_ptr<Matrix> C_;

    /// MO "eigenvalues"
    boost::shared_ptr<Vector> evals_;

    /// AO basis set
    boost::shared_ptr<BasisSet> basis_;
    /// Integral factory that as
    boost::shared_ptr<IntegralFactory> ints_;

    /// MO Dimensionality
    Dimension dim_; // dim_.n() better equal nirrep_

    MOIndexSpace();
public:
    MOIndexSpace(const std::string& name,
                 const boost::shared_ptr<Matrix>& full_C,   // Should this be 4 C's instead?
                 const boost::shared_ptr<Vector>& evals,
                 const boost::shared_ptr<BasisSet>& basis,
                 const boost::shared_ptr<IntegralFactory>& ints);

    MOIndexSpace(const std::string& name,
                 const boost::shared_ptr<Wavefunction>& wave);

    int nirrep() const;
    const std::string& name() const;

    /// C - transformation matrix (AO x MO)
    const boost::shared_ptr<Matrix>& C() const;

    /// "Eigenvalues" of the C matrix
    const boost::shared_ptr<Vector>& evals() const;

    /// The AO basis set used to create C
    const boost::shared_ptr<BasisSet>& basis() const;

    /// Integral factory used to create C
    const boost::shared_ptr<IntegralFactory>& integral() const;

    /// MO dimensionality
    const Dimension& dim() const;

    /** Creates an MOIndexSpace from 'from' to the given basis set 'to'
      */
    static MOIndexSpace transform(const MOIndexSpace& from, const boost::shared_ptr<BasisSet>& to);

    /** Returns the overlap matrix between space1 and space2.
        The matrix has dimensions of space2.C().coldim() and
        space1.C().coldim().
        Throws if the overlap cannot be computed.
      */
    static boost::shared_ptr<Matrix> overlap(const MOIndexSpace& space1, const MOIndexSpace& space2);
    /** Returns the overlap matrix between basis1 and basis2.
        Throws if the overlap cannot be computed.
      */
    static boost::shared_ptr<Matrix> overlap(const boost::shared_ptr<BasisSet>& basis1,
                                             const boost::shared_ptr<BasisSet>& basis2);
};

}

#endif // _psi_src_lib_libmints_moindexspace_h_
