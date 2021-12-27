#include <stdlib.h>
#include <iostream>
#include <gmock/gmock.h>

using testing::Return;

class DZ_Class {

    public:
    DZ_Class(){};
    virtual long int get_meas(){
        return (random() - 10000);
    };

};

class DZ_Class_mock : public DZ_Class {

    public:
    MOCK_METHOD0(get_meas, long int(void));

};

class SUT_Class {

    protected:
    bool m_DZ_Class_is_mocked;
    public:
    DZ_Class m_dz_object;
    DZ_Class_mock m_dz_object_mock;

    SUT_Class(){
        m_DZ_Class_is_mocked = false;
    };

    void set_is_DZ_Class_mocked(bool is_mocked) {
        m_DZ_Class_is_mocked = is_mocked;
    }

    double get_data() {
        // Note that div by zero might occur here if get_meas returns 0.
        // Testing can take a long time if we wait for getting such a case where
        // get_meas would return 0. Better to go with mocks to emulate certain
        // random values.
        if (m_DZ_Class_is_mocked) {
            return static_cast<double>( 
                1000000.0 / static_cast<double>(
                    m_dz_object_mock.get_meas()) );
        } else  {
            return static_cast<double>( 
                1000000.0 / static_cast<double>(
                    m_dz_object.get_meas()) );
        }
    }

};

TEST(DivByZeroTesting, MeasReturnsZero) {

    srandom(256);

    SUT_Class a_SUT_obj;
    a_SUT_obj.set_is_DZ_Class_mocked(true);

    EXPECT_CALL(a_SUT_obj.m_dz_object_mock, get_meas())
        .WillOnce(Return(0));

    std::cout << std::to_string( a_SUT_obj.get_data() ) << std::endl;

}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
