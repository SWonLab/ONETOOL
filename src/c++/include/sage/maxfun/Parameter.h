#ifndef PARAMETER_H
#define PARAMETER_H

#include "sage/maxfun/CovarianceMatrix.h"


namespace SAGE   {
namespace MAXFUN {

class Parameter
{
public:

  MEM_FRIEND(SAGE::MAXFUN::Parameter);

  /// \brief Identifies the estimation type for a given parameter.
  ///
  /// Paramtype indicates how that parameter should be treated by Maxfun.
  ///
  /// Please note that only \c INDEPENDENT_FUNCTIONAL, \c INDEPENDENT, \c DEPENDENT, and \c FIXED
  /// should be used as \b initial types. Maxfun may change their type during maximization, but the user should \b not
  /// use any type other than those in the preceeding list as \b initial types.
  enum ParamTypeEnum 
  { 
    NO_PARAMTYPE                  = 0,  /*!< \hideinitializer No specified type. */
    INDEPENDENT_FUNCTIONAL        = 1,  /*!< \hideinitializer Independent, involved in functional relationship with other parameter(s). */
    INDEPENDENT                   = 2,  /*!< \hideinitializer Independent, not involved in function relationship with other parameters. */
    DEPENDENT                     = 3,  /*!< \hideinitializer Dependent on (calculated from) other parameter(s). */
    FIXED                         = 4,  /*!< \hideinitializer Fixed (externally to MAXFUN) */
    IND_FUNC_FIXED_AT_BOUND       = 5,  /*!< \hideinitializer Independent, involved in functional relationship, fixed by MAXFUN at bound */
    IND_FIXED_AT_BOUND            = 6,  /*!< \hideinitializer Independent, not involved in functional relationship, fixed by MAXFUN at bound */
    IND_FUNC_FIXED_NEAR_BOUND     = 7,  /*!< \hideinitializer Independent, involved in functional relationship, fixed by MAXFUN near bound */
    IND_FIXED_NEAR_BOUND          = 8,  /*!< \hideinitializer Independent, not involved in functional relationship, fixed by MAXFUN near bound */
    IND_FUNC_FIXED_NOT_NEAR_BOUND = 9,  /*!< \hideinitializer Independent, involved in functional relationship, fixed by MAXFUN not near bound */
    IND_FIXED_NOT_NEAR_BOUND      = 10   /*!< \hideinitializer Independent, not involved in functional relationship, fixed by MAXFUN not near bound */
  };

  enum PValueOptionEnum 
  {
    ONE_SIDED = 0, /*!< \hideinitializer P-value will be one-sided. */
    TWO_SIDED = 1  /*!< \hideinitializer P-value will be two-sided. */
  };

  friend class ParameterMgr;
  friend class Maximizer;

  /// @name Constructors & operators
  //@{
    // Default constructor
    Parameter();

    ///
    /// Copy constructor
    /// \param other The Parameter whose contents will be copied into this object.
    Parameter(const Parameter & other);

    ///
    /// Destructor
    ~Parameter();

    ///
    /// Assignment operator
    /// \param other The Parameter whose contents will be copied into this object.
    Parameter& operator=(const Parameter & other);

  //@}

  /// @name Basic information
  //@{  

    ///
    /// Returns the name of the parameter.
    const string getName() const;

    ///
    /// Returns the name of the group to which this parameter belongs. Please note that if no grouping information was passed when this parameter was created, the group name will be reported as \c "GLOBAL".
    const string getGroupName() const;

    ///
    /// Returns the index number of the parameter. If, for instance,
    /// this parameter was the third parameter to be added, then getIndex()
    /// will return 2 (with indices starting at 0).
    size_t getIndex() const;

    ///
    /// Returns the index number of the parameter within its group. If, for instance,
    /// this parameter was the second parameter to be added to its group, then getGroupIndex()
    /// will return 1 (with indices starting at 0).
    size_t getGroupIndex() const;

    ///
    /// Returns whether or not the parameter is in use. See setInUse() for more information.
//    bool isInUse() const;

    ///
    /// If you need to disable a parameter for any reason, you can use isInUse() function
    /// to do so. Simply invoke \code setInUse(false) \endcode , and the parameter will not actually be
    /// used in the maximization. By default, isInUse() is set to \c true.
    ///
    /// isInUse() is only interpreted at the point where you invoke MAXFUN::Maximize(). At that point,
    /// parameters are actually dynamically added to Maxfun. If any parameter is marked as \b not
    /// in use, then MAXFUN::Maximize() will not add the parameter.
    ///
    /// Please note that changing a parameter's isInUse() status does \b not affect the parameter's
    /// other options. You can turn on and off a parameter's isInUse() status without affecting
    /// any other options.
    /// \param in_use Indicates whether or not the parameter is in use.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
//    int setInUse(bool in_use);

    ///
    /// Sets options for how this parmaeter's p-value will be calculated.
    /// \param opt P-values can be either one-sided or two-sided. Please consult 
    /// MAXFUN::Parameter::PValueOptionEnum for more details.
    /// \param mean The mean value against which the p-value will be calculated.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    ///
    /// Please note that the default option is \c TWO_SIDED with \c mean = 0.0.
    int setPValueInf(PValueOptionEnum opt = TWO_SIDED, double mean = 0.0);

    ///
    /// Returns information about how this parameter's p-value will be calculated.
    /// \returns A std::pair whose first element is a MAXFUN::Parameter::PValueOptionEnum and whose second element is the mean.
    pair<PValueOptionEnum, double> getPValueInf() const;

  //@}  

  /// @name Pre-maximization information
  //@{

    ///
    /// Returns the initial estimate.
    double getInitialEstimate() const;

    ///
    /// Returns the initial estimate.
    int setInitialEstimate(double);

    ///
    /// Sets the initial type.
    /// \param p The initial type to be set.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setInitialType(ParamTypeEnum p);

    /// (due to JA, introduced to  facilitate the score test)
    /// Sets the final type.
    /// \param p The initial type to be set.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setFinalType(ParamTypeEnum p);

    ///
    /// Returns the initial parameter type.
    ParamTypeEnum getInitialType() const;

    ///
    /// Returns \c true if the initial type is INDEPENDENT or INDEPENDENT_FUNCTIONAL;
    /// returns \c false otherwise.
    bool isEstimated() const;

    ///
    /// Sets the lower bound for this parameter's estimation.
    /// \param lower_bound The new lower bound.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setLowerBound(double lower_bound);

    ///
    /// Returns the lower bound.
    double getLowerBound() const;

    ///
    /// Sets the upper bound for this parameter's estimation.
    /// \param upper_bound The new upper bound.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setUpperBound(double upper_bound);

    ///
    /// Returns the upper bound for this parameter's estimation.
    double getUpperBound() const;

    ///
    /// Sets the initial stepsize factor for this parameter's estimation.
    /// \param init_stepsize The initial stepsize factor.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setInitialStepsizeFactor(double init_stepsize);

    ///
    /// Returns the initial stepsize factor for this parameter's estimation.
    double getInitialStepsizeFactor() const;

  //@}

  /// @name Maximization runtime information
  //@{

    ///
    /// Returns the current estimate.
    double operator() () const;

    ///
    /// Returns the current estimate.
    double & operator() ();

    ///
    /// Sets the current estimate.
    /// Note: the 'previous estimate' will be automatically set whenever setCurrentEstimate is invoked).
    /// \param current_estimate The new current estimate.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setCurrentEstimate(double current_estimate);

    ///
    /// Returns the current estimate.
    double getCurrentEstimate() const;
    
    ///
    /// Returns whatever the previous estimate was.
    double getPreviousEstimate() const;
    
    ///
    /// Returns true if the current estimate differs from the previous estimate; false otherwise.
    bool estimateChanged() const;

  //@}

  /// @name Post-maximization information
  //@{

    ///
    /// Sets the final estimate.
    /// \param final_estimate The new final estimate.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setFinalEstimate(double final_estimate);

    ///
    /// Returns the final estimate.
    double getFinalEstimate() const;

    ///
    /// Returns the final type
    ///
    /// Please note that in the course of maximization, Maxfun may
    /// change the type of the parameter. For instance, if an independent parameter
    /// estimates at a bound, its final type will be "fixed at bound".
    ParamTypeEnum getFinalType() const;

    ///
    /// Returns whether or not the getFinalType() reflects a fixed status.
    /// \retval true If getFinalType() is \c FIXED, \c IND_FUNC_FIXED_AT_BOUND,
    /// \c IND_FIXED_AT_BOUND, \c IND_FUNC_FIXED_NEAR_BOUND, \c IND_FIXED_NEAR_BOUND,
    /// \c IND_FUNC_FIXED_NOT_NEAR_BOUND, or \c IND_FIXED_NOT_NEAR_BOUND.
    /// \retval false If getFinalType() is \c INDEPENDENT_FUNCTIONAL, \c INDEPENDENT, or 
    /// \c DEPENDENT.
    bool isFinalFixed() const;

    ///
    /// Identifies whether or not a standard error is available.
    bool isStdErrorAvailable() const;

    ///
    /// Returns the standard error.
    ///
    /// Please note that before using this function, you should make sure that
    /// a standard error is available by using the isStdErrorAvailable() function.
    double getStdError() const;

    ///
    /// Sets the standard error.
    ///
    /// Please note that before using this function, you should make sure that
    /// a standard error is available by using the isStdErrorAvailable() function.
    /// \param std_error The new standard error.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setStdError(double std_error);

    ///
    /// Identifies whether or not a first partial derivative is available.
    bool isDerivAvailable() const;

    ///
    /// Returns the first partial derivative.
    ///
    /// Please note that before using this function, you should make sure that
    /// a derivative is available by using the isDerivAvailable() function.
    double getDeriv() const;

    ///
    /// Sets the first partial derivative.
    ///
    /// Please note that before using this function, you should make sure that
    /// a derivative is available by using the isDerivAvailable() function.
    /// \param deriv The new first partial derivative.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setDeriv(double deriv);

    ///
    /// If this parameter's InitialType is anything other than MAXFUN::Parameter::FIXED, and
    /// Maxfun was instructed to compute a variance-covariance matrix (see MAXFUN::RunCfg),
    /// then there should be a set of variances/covariances available for this parameter. This
    /// function (isVarAvailable()) indicates \c true if such a matrix is available.
    bool isVarAvailable() const;

    ///
    /// Returns the index number of this parameter's variance (if available).
    /// This index number is used in conjunction with the MAXFUN::CovarianceMatrix.
    size_t getVarIndex() const;

    ///
    /// Identifies whether or not a p-value is available.
    bool isPValueAvailable() const;

    ///
    /// Returns the p-value.
    ///
    /// Please note that before using this function, you should make sure that
    /// a p-value is available by using the p_value_available() function.
    double getPValue() const;

  //@}

  /// @name Output formatting
  //@{

    ///
    /// Returns the abbreviated name. In cases where, for whatever reason, there is
    /// not enough space to print out the entire name, then the abbreviated name will
    /// be used. You can use the FormatName() function to produce this output behavior.
    const string getNameAbbr() const;

    ///
    /// Sets the abbreviated name.
    /// \param name_abbr The new abbreviated name.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setNameAbbr(string name_abbr);

    ///
    /// Returns whether or not a parameter will be included in the FormatEstimates() output.
    /// Set setIncludeInOutput() for more information.
    bool getIncludeInOutput() const;

    ///
    /// You can set whether or not you want an entire parameter reported in the FormatEstimates()
    /// output. Simply invoke \code setIncludeInOutput(false) \endcode . Please note that setIncludeInOutput() is
    /// \c true by default.
    /// \param include Indicates whether or not to include this variable in final output.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setIncludeInOutput(bool include);

    ///
    /// Returns whether or not the parameter's derivative will be reported.
    /// See setIncludeDeriv() for more information.
    bool getIncludeDeriv() const;       

    ///
    /// You can set whether or not you want the parameter's derivative to be reported with this function.
    ///
    /// Please note that this option is enabled by default.
    /// \param include Indicates whether or not to include this variable's derivative in the final output.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setIncludeDeriv(bool include);

    ///
    /// Returns whether or not the parameter's standard error will be reported.
    /// Please set setIncludeStdError() for more information.
    bool getIncludeStdError() const;         

    ///
    /// If setIncludeStdError() is set to true, then the parameter's standard will be reported 
    /// in the formatted output.
    /// \param include Indicates whether or not to include this variable's standard error in the final output.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setIncludeStdError(bool include);             

    ///
    /// Returns whether or not the parameter's p-value will be reported.
    /// Please see setIncludePValue() for more information.
    bool getIncludePValue() const;

    ///
    /// If setIncludePValue() is set to true, then the parameter's p-value will be reported
    /// in the formatted output.
    ///
    /// Please note that this option is enabled by default.
    /// \param include Indicates whether or not to include this variable's p-value in the final output.
    /// \retval 0 Value was set successfully.
    /// \retval 1 Value was not set successfully.
    int setIncludePValue(bool include);
    
    // Dumps the internal contents of the parameter to debug.os
    //void dump(DebugCfg & debug) const;      

    bool scoretest; // tells us if we have to do a score test

  //@}

    ///

  protected:

  // Functions NOT documented in the API (with good reason!)

    // Copy operation (for copy constructor and assignment operator)
    void copy(const Parameter &);

    // Once a maximization has been performed, this function is automatically invoked to transfer
    // the maximization results into the class.
    void updateFinalOutput(const Maxfun_Data & data, CovarianceMatrix&, int cov_matrix_status);

    // Identifies whether or not the parameter's current estimate is within established bounds.
    bool isInBounds() const;
    size_t getDerivIndex() const;

    int setName       (string name);
    int setGroupName  (string group_name);
    int setIndex      (size_t index);
    int setGroupIndex (size_t group_index);
    int setDerivIndex (size_t deriv_index);
    int setVarIndex   (size_t var_index);

    void calculatePValue         ();
    void calculatePValueOneSided ();
    void calculatePValueTwoSided ();


  private:

      //===================================================================
      // Basic info:
      //===================================================================

    string              my_Name;
    string              my_NameAbbr;

//    bool                my_InUse;

      //===================================================================
      // Values:
      //===================================================================

    double              my_InitialEstimate,
                        my_PreviousEstimate,
                        my_CurrentEstimate,
                        my_FinalEstimate;

      //===================================================================
      // Initial/final status:
      //===================================================================

    ParamTypeEnum       my_InitialType,
                        my_FinalType;

      //===================================================================
      // Bounds:
      //===================================================================

    double              my_LowerBound,
                        my_UpperBound;

      //===================================================================
      // Initial stepsize factor (STPIN):
      //===================================================================

    double              my_InitialStepsizeFactor;

      //===================================================================
      // Standard error / 1st partial derivative:
      //===================================================================

    bool                my_StdErrorAvailable;
    double              my_StdError;
    bool                my_DerivAvailable;
    double              my_Deriv;

      //===================================================================
      // P-value:
      //===================================================================

    PValueOptionEnum    my_pvalue_opt;
    double              my_pvalue_mean;
    bool                my_pValueAvailable;
    double              my_pValue; 

      //===================================================================
      // Indices:
      //===================================================================

    size_t              my_Index;
    size_t              my_GroupIndex;
    size_t              my_DerivIndex;
    size_t              my_VarIndex;

      //===================================================================
      // Grouping:
      //===================================================================

    string              my_GroupName;

      //===================================================================
      // Output formatting:
      //===================================================================

    bool                my_IncludeInOutput;
    bool                my_IncludeStdError;
    bool                my_IncludepValue;
    bool                my_IncludeDeriv;

      //===================================================================
      // Covariance information
      //===================================================================

    bool               my_VarAvailable;
};

typedef vector<Parameter>               param_vector;
typedef vector<param_vector::size_type> param_group;

/** \class ParameterIterator
 *  \brief Non-const iterator across MAXFUN::Parameter's
 *
 */
class ParameterIterator
{
  public:
  // Friends
  friend class ParameterMgr;
  friend class ParameterConstIterator;
  
  // Typedefs
  typedef ParameterIterator        iterator;
  //typedef ParameterConstIterator   const_iterator;
  typedef Parameter              & reference;
  typedef Parameter              * pointer;
  typedef const Parameter        * const_pointer;
  typedef const Parameter        & const_reference;
  typedef Parameter                value_type;
  typedef param_group::difference_type   difference_type;
  typedef param_group::size_type         size_type;
  typedef random_access_iterator_tag     iterator_category;

  // Constructor
  ParameterIterator();

  // Copy constructor
  ParameterIterator(const ParameterIterator &);

  // Dereference
  reference operator*  ();
  reference operator[] (difference_type i);

  pointer operator-> ();

  // Increment/Decrement

  iterator operator++ ();
  iterator operator++ (int);
  iterator operator-- ();
  iterator operator-- (int);
  iterator operator+= (difference_type i);
  iterator operator-= (difference_type i);
  iterator operator+  (difference_type i) const;
  iterator operator-  (difference_type i) const;

  difference_type operator-(const iterator & x) const;

  // Comparison

  bool operator== (const iterator & x) const;
  bool operator!= (const iterator & x) const;
  bool operator<  (const iterator & x) const;

  protected:

  // Constructor
  ParameterIterator(param_vector *, param_group::iterator);

  private:

  // Reference to the master list of parameters
  param_vector * masterlist;

  // Iterator to the current element of this group:
  param_group::iterator iter;

  void increment();
  void decrement();
};

/** \class ParameterConstIterator
 *  \brief Const iterator across MAXFUN::Parameter's
 *
 */
class ParameterConstIterator
{
  public:
  // Friends
  friend class ParameterMgr;
  
  // Typedefs
  typedef ParameterIterator             iterator;
  typedef ParameterConstIterator       const_iterator;
  typedef Parameter              & reference;
  typedef Parameter              * pointer;
  typedef const Parameter        * const_pointer;
  typedef const Parameter        & const_reference;
  typedef Parameter                value_type;
  typedef param_group::difference_type   difference_type;
  typedef param_group::size_type         size_type;
  typedef random_access_iterator_tag     iterator_category;

  // Constructor
  ParameterConstIterator();

  // Copy constructor
  ParameterConstIterator(const ParameterConstIterator &);
  ParameterConstIterator(const ParameterIterator       &);

  // Dereference
  const_reference operator*  ()                  const;
  const_reference operator[] (difference_type i) const;

  const_pointer operator-> ();

  // Increment/Decrement

  const_iterator operator++ ();
  const_iterator operator++ (int);
  const_iterator operator-- ();
  const_iterator operator-- (int);
  const_iterator operator+= (difference_type i);
  const_iterator operator-= (difference_type i);
  const_iterator operator+  (difference_type i) const;
  const_iterator operator-  (difference_type i) const;

  difference_type operator-(const const_iterator & x) const;

  // Comparison

  bool operator== (const const_iterator & x) const;
  bool operator!= (const const_iterator & x) const;
  bool operator<  (const const_iterator & x) const;

  protected:

  // Constructor
  ParameterConstIterator(const param_vector *, param_group::const_iterator);

  private:

  void increment();
  void decrement();

  // Reference to the master list of parameters
  const param_vector * masterlist;

  // Iterator to the current element of this group:
  param_group::const_iterator iter;
};

///
/// Converts a ParamTypeEnum into a human readable string.
/// \param p The ParamTypeEnum to be converted.
string ParamTypeEnum2str(Parameter::ParamTypeEnum p);

} /// End of namespace MAXFUN

    /// Returns the bytecount in memory.
MEM_COUNT_BEGIN(MAXFUN::Parameter)
{
  return get_mem(t.my_Name) + get_mem(t.my_NameAbbr) + sizeof(SAGE::MAXFUN::Parameter);
}
MEM_COUNT_END

} // End of namespace SAGE

#include "sage/maxfun/Parameter.ipp"

#endif

