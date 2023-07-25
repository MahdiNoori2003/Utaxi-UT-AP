CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp logic/Manager.hpp logic/Exception.hpp logic/Travel.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp logic/Exception.hpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Manager.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Passenger.o $(BUILD_DIR)/Driver.o  $(BUILD_DIR)/Io.o $(BUILD_DIR)/Travel.o $(BUILD_DIR)/Exception.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Manager.o  $(BUILD_DIR)/User.o $(BUILD_DIR)/Passenger.o $(BUILD_DIR)/Driver.o  $(BUILD_DIR)/Io.o $(BUILD_DIR)/Travel.o $(BUILD_DIR)/Exception.o -o myserver.out

$(BUILD_DIR)/Manager.o: logic/Manager.hpp logic/Manager.cpp logic/Driver.hpp logic/Passenger.hpp logic/Travel.hpp logic/User.hpp logic/Io.hpp logic/Exception.hpp
	$(CC) $(CF) -c logic/Manager.cpp -o $(BUILD_DIR)/Manager.o

$(BUILD_DIR)/Io.o: logic/Io.hpp logic/Io.cpp logic/Travel.hpp logic/Exception.hpp
	$(CC) $(CF) -c logic/Io.cpp -o $(BUILD_DIR)/Io.o

$(BUILD_DIR)/User.o: logic/User.hpp logic/User.cpp
	$(CC) $(CF) -c logic/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Passenger.o: logic/Passenger.hpp logic/Passenger.cpp logic/User.hpp
	$(CC) $(CF) -c logic/Passenger.cpp -o $(BUILD_DIR)/Passenger.o

$(BUILD_DIR)/Driver.o: logic/Driver.hpp logic/Driver.cpp logic/User.hpp
	$(CC) $(CF) -c logic/Driver.cpp -o $(BUILD_DIR)/Driver.o

$(BUILD_DIR)/Travel.o: logic/Travel.hpp logic/Travel.cpp
	$(CC) $(CF) -c logic/Travel.cpp -o $(BUILD_DIR)/Travel.o

$(BUILD_DIR)/Exception.o: logic/Exception.hpp logic/Exception.cpp
	$(CC) $(CF) -c logic/Exception.cpp -o $(BUILD_DIR)/Exception.o


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
