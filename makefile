all: 
	g++ -std=c++11 -o mock-test-div-zero mock_test_div_zero.cpp -lpthread -lgtest -lgmock
	
clean:
	rm -f *.o *~ core 
