all: dbconn

dbconn: dbconn.cpp 
	g++ -o dbconn dbconn.cpp -lnanodbc -lodbc -Wall

clean:
	rm dbconn
