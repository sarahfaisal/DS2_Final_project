#include "plots/pbPlots.hpp"
#include "plots/supportLib.hpp"
#include"src/skiplist.cpp"
//#include "src/AVLIndex.hpp"
#include "src/AVLIndex.cpp"
#include <chrono>
#include <vector>
#include <random> // For random number generation
#include <algorithm> // For shuffle
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
struct Car {
    double ID;
    std::string Brand;
    std::string Model;
    int Year;
    std::string Color;
    int Mileage;
    int Price;
    std::string Condition;
};

typedef int KeyType;
typedef int IndexType;
SkipList<int> skiplist{0.5};
SkipList<int> skiplist_probability_zero_point_two_five{0.25};
SkipList<int> skiplist_probability_zero_point_one_two_five{0.125};
// MySkipList skiplist{0.5};
// MySkipList skiplist_probability_zero_point_two_five{0.25};
// MySkipList skiplist_probability_zero_point_one_two_five{0.125};
//AVLIndex<KeyType, IndexType> avl;
avl_tree avl;
std::vector<Car> cars;
std::vector<int> test_data;

// Function to read data from CSV file
void ReadCSV(const std::string& filename) {
    //std::vector<Car> cars; // Vector to store cars

    std::ifstream file(filename); // Open file
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return; // Return empty vector if file not opened
    }

    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Car car;
        char comma; // To store the comma separator

        // Read each field separated by commas
        ss >> car.ID >> comma;
		test_data.push_back(car.ID);
        std::getline(ss, car.Brand, ',');
        std::getline(ss, car.Model, ',');
        ss >> car.Year >> comma;
        std::getline(ss, car.Color, ',');
        ss >> car.Mileage >> comma;
        ss >> car.Price >> comma;
        std::getline(ss, car.Condition, ',');

        // Add the car to the vector
        cars.push_back(car);
    }

    // Close the file
    file.close();

    return;
}
int Draw_single_graph(vector<double> xs, vector<double> ys, std::string filename, std::vector<wchar_t>* graph_title){//, std::string X_lable,std::string y_lable){
	bool success;
	StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &xs;
	series->ys = &ys;
	series->linearInterpolation = true;
	series->lineType = toVector(L"solid");
	series->lineThickness = 2;
	series->color = CreateRGBColor(1, 0, 1);
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = graph_title;
	settings->yLabel = toVector(L"Data Size");
	settings->xLabel = toVector(L"Time(milliseconds)");
	settings->scatterPlotSeries->push_back(series);
	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
	if(success){
		vector<double> *pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, filename);
		DeleteImage(imageReference->image);
	}
	else{
		cerr << "Error: ";
		for(wchar_t c : *errorMessage->string){
			wcerr << c;
		}
		cerr << endl;
	}

	FreeAllocations();

	return success ? 0 : 1;
}
int draw_multi_line_graph(
	vector<double> xsa, 
	vector<double> ysa, 
	vector<double> xs, 
	vector<double> ys,
	std::string filename, 
	std::vector<wchar_t>* graph_title
	)
{
	bool success;
	StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &xs;
	series->ys = &ys;
	series->linearInterpolation = true;
	series->lineType = toVector(L"solid");
	series->lineThickness = 2;
	series->color = CreateRGBColor(1, 0, 0);
	ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &xsa;
	series2->ys = &ysa;
	series2->linearInterpolation = true;
	series2->lineType = toVector(L"solid");
	series2->lineThickness = 2;
	series2->color = CreateRGBColor(0, 0, 1);
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = graph_title;//toVector(L"");
	settings->yLabel = toVector(L"Data Size");
	settings->xLabel = toVector(L"Time(milliseconds)");
	settings->scatterPlotSeries->push_back(series);
	settings->scatterPlotSeries->push_back(series2);
	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
	if(success){
		vector<double> *pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata,filename);
		DeleteImage(imageReference->image);
	}else{
		cerr << "Error: ";
		for(wchar_t c : *errorMessage->string){
			cerr << c;
		}
		cerr << endl;
	}

	FreeAllocations();

	return success ? 0 : 1;
}
 int draw_three_line_graph(
	vector<double> xsa, 
	vector<double> ysa, 
	vector<double> xs, 
	vector<double> ys,
	vector<double> xsb, 
	vector<double> ysb,
	std::string filename, 
	std::vector<wchar_t>* graph_title
	)
{
	bool success;
	StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &xs;
	series->ys = &ys;
	series->linearInterpolation = true;
	series->lineType = toVector(L"solid");
	series->lineThickness = 2;
	series->color = CreateRGBColor(1, 0, 0);
	ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &xsa;
	series2->ys = &ysa;
	series2->linearInterpolation = true;
	series2->lineType = toVector(L"solid");
	series2->lineThickness = 2;
	series2->color = CreateRGBColor(0, 0, 1);
	ScatterPlotSeries *series3 = GetDefaultScatterPlotSeriesSettings();
	series3->xs = &xsb;
	series3->ys = &ysb;
	series3->linearInterpolation = true;
	series3->lineType = toVector(L"solid");
	series3->lineThickness = 2;
	series3->color = CreateRGBColor(1, 0, 1);
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = graph_title;//toVector(L"");
	settings->yLabel = toVector(L"Data Size");
	settings->xLabel = toVector(L"Time(milliseconds)");
	settings->scatterPlotSeries->push_back(series);
	settings->scatterPlotSeries->push_back(series2);
	settings->scatterPlotSeries->push_back(series3);
	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
	if(success){
		vector<double> *pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata,filename);
		DeleteImage(imageReference->image);
	}else{
		cerr << "Error: ";
		for(wchar_t c : *errorMessage->string){
			cerr << c;
		}
		cerr << endl;
	}

	FreeAllocations();

	return success ? 0 : 1;
}
void compare_inset_time()
{
	//int arraySize = 10000;
	//std::vector<double> test_data = cars_ID;//generateRandomVector(arraySize);
	std::vector<double> x_skiplist_probability_one_point_five2;
	std::vector<double> y_skiplist_probability_one_point_five2;
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < test_data.size(); ++i)
	{	
		if(i% (test_data.size()/4)==0)
		{
			skiplist.insert(test_data[i]);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end - start;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_one_point_five2.push_back(load_time_milliseconds_double);
			y_skiplist_probability_one_point_five2.push_back(static_cast<double>(i));
		}
		else
		{
			skiplist.insert(test_data[i]);
		}
	}

	std::vector<double> x_skiplist_probability_zero_point_two_five2;
	std::vector<double> y_skiplist_probability_zero_point_two_five2;
	auto start3 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < test_data.size(); ++i)
	{	if(i% (test_data.size()/4)==0)
		{
			skiplist_probability_zero_point_two_five.insert(test_data[i]);
			auto end3 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end3 - start3;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_zero_point_two_five2.push_back(load_time_milliseconds_double);
			y_skiplist_probability_zero_point_two_five2.push_back(static_cast<double>(i));
		}
		else
		{
			skiplist_probability_zero_point_two_five.insert(test_data[i]);
		}
	}

	std::vector<double> x_skiplist_probability_zero_point_one_two_five2;
	std::vector<double> y_skiplist_probability_zero_point_one_two_five2;
	auto start4 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < test_data.size(); ++i)
	{	if(i% (test_data.size()/4)==0)
		{
			skiplist_probability_zero_point_one_two_five.insert(test_data[i]);
			auto end4 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end4 - start4;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_zero_point_one_two_five2.push_back(load_time_milliseconds_double);
			y_skiplist_probability_zero_point_one_two_five2.push_back(static_cast<double>(i));
		}
		else
		{
			skiplist_probability_zero_point_one_two_five.insert(test_data[i]);
		}
	}

	std::vector<double> xs2;
	std::vector<double> ys2;
	auto start2 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < test_data.size(); ++i) //test_data.size()
	{	if(i % (test_data.size()/4)==0)
		{
			r = avl.insert(r, test_data[i]);
			auto end2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end2 - start2;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			 //"Load time: " << load_time_milliseconds_double<<std::endl;
			xs2.push_back(load_time_milliseconds_double );
			ys2.push_back(static_cast<double>(i));
		}
		else
		{
			//std::cout <<" ";
			r = avl.insert(r, test_data[i]);
		}
	}
	//avl.printTree(r,0);
	Draw_single_graph(x_skiplist_probability_one_point_five2, y_skiplist_probability_one_point_five2, "SkipList_insert_graph.png",toVector(L"SkipList Insert(p=0.5)"));
	Draw_single_graph(xs2, ys2, "AVL_Tree_insert_graph.png",toVector(L"AVL Tree insert"));
	draw_multi_line_graph(x_skiplist_probability_one_point_five2, y_skiplist_probability_one_point_five2,xs2,ys2,"AVL_Tree_vs_SkipList_insert_graph.png",toVector(L"SkipList(BLUE)(p=0.5) V/S AVL tree(RED) insert"));
	draw_three_line_graph(x_skiplist_probability_one_point_five2, y_skiplist_probability_one_point_five2,x_skiplist_probability_zero_point_two_five2,y_skiplist_probability_zero_point_two_five2,x_skiplist_probability_zero_point_one_two_five2,y_skiplist_probability_zero_point_one_two_five2,"SkipList_vs_SkipList_insert_(probability)_graph.png",toVector(L"SkipList(BLUE)(p=0.5), (RED)(p=0.25), purpel(p=0.125) insert"));
	return;
}


std::vector<int> generateRandomVector(int size) {
    std::vector<int> result(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-5000, 15000);

    for (int i = 0; i < size; ++i) {
        result[i] = dist(gen);
    }

    return result;
}

void compare_scearch_time()
{
	int vectorSize = 10000;
    std::vector<int> randomVector = generateRandomVector(vectorSize);

	std::vector<double> x_skiplist_probability_one_point_five;
	std::vector<double> y_skiplist_probability_one_point_five;
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < randomVector.size(); ++i)
	{	
		if(i% (randomVector.size()/4)==0)
		{
			//std::cout<<skiplist.search(randomVector[i])<<std::endl;
			skiplist.search(randomVector[i]);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end - start;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_one_point_five.push_back(load_time_milliseconds_double);
			y_skiplist_probability_one_point_five.push_back(static_cast<double>(i));
		}
		else
		{
			//std::cout<< skiplist.search(randomVector[i])<<" "<< randomVector[i] << std::endl;
			//std::cout<<skiplist.search(randomVector[i])<<std::endl;
			skiplist.search(randomVector[i]);
		}
	}

	std::vector<double> x_skiplist_probability_zero_point_two_five;
	std::vector<double> y_skiplist_probability_zero_point_two_five;
	auto start3 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < randomVector.size(); ++i)
	{	if(i% (randomVector.size()/4)==0)
		{
			skiplist_probability_zero_point_two_five.search(randomVector[i]);
			auto end3 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end3 - start3;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_zero_point_two_five.push_back(load_time_milliseconds_double);
			y_skiplist_probability_zero_point_two_five.push_back(static_cast<double>(i));
		}
		else
		{
			skiplist_probability_zero_point_two_five.search(randomVector[i]);
		}
	}

	std::vector<double> x_skiplist_probability_zero_point_one_two_five;
	std::vector<double> y_skiplist_probability_zero_point_one_two_five;
	auto start4 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < randomVector.size(); ++i)
	{	if(i% (randomVector.size()/4)==0)
		{
			skiplist_probability_zero_point_one_two_five.search(randomVector[i]);
			auto end4 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end4 - start4;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_zero_point_one_two_five.push_back(load_time_milliseconds_double);
			y_skiplist_probability_zero_point_one_two_five.push_back(static_cast<double>(i));
		}
		else
		{
			skiplist_probability_zero_point_one_two_five.search(randomVector[i]);
		}
	}

	std::vector<double> xs;
	std::vector<double> ys;
	auto start2 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < randomVector.size() ; ++i) //randomVector.size()
	{	
		if(i% (randomVector.size()/4)==0)
		{
			avl.search(r, randomVector[i]);
			auto end2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end2 - start2;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			//std::cout<<"load_time_milliseconds avl: "<<load_time_milliseconds_double<<std::endl;
			xs.push_back(load_time_milliseconds_double);
			ys.push_back(static_cast<double>(i));
		}
		else
		{
			//std::cout <<" ";
			avl.search(r, randomVector[i]);
		}
	}
	Draw_single_graph(x_skiplist_probability_one_point_five, y_skiplist_probability_one_point_five, "SkipList_search_graph.png",toVector(L"SkipList search(p=0.5)"));
	Draw_single_graph(xs, ys, "AVL_Tree_search_graph.png",toVector(L"AVL Tree search"));
	draw_multi_line_graph(x_skiplist_probability_one_point_five, y_skiplist_probability_one_point_five,xs,ys,"AVL_Tree_vs_SkipList_search_graph.png",toVector(L"SkipList(BLUE)(p=0.5) V/S AVL tree(RED) search"));
	draw_three_line_graph(x_skiplist_probability_one_point_five, y_skiplist_probability_one_point_five,x_skiplist_probability_zero_point_two_five,y_skiplist_probability_zero_point_two_five,x_skiplist_probability_zero_point_one_two_five,y_skiplist_probability_zero_point_one_two_five,"SkipList_vs_SkipList_search_(probability)_graph.png",toVector(L"SkipList(BLUE)(p=0.5), (RED)(p=0.25), purpel(p=0.125) search"));
	return;
}
void compare_delete_time()
{
	//int arraySize = 10000;
	//std::vector<double> test_data = cars_ID;//generateRandomVector(arraySize);
	std::vector<double> x_skiplist_probability_one_point_five2;
	std::vector<double> y_skiplist_probability_one_point_five2;
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < test_data.size(); ++i)
	{	
		if(i% (test_data.size()/4)==0)
		{
			skiplist.remove(test_data[i]);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end - start;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_one_point_five2.push_back(load_time_milliseconds_double);
			y_skiplist_probability_one_point_five2.push_back(static_cast<double>(i));
		}
		else
		{
			skiplist.remove(test_data[i]);
		}
	}

	std::vector<double> x_skiplist_probability_zero_point_two_five2;
	std::vector<double> y_skiplist_probability_zero_point_two_five2;
	auto start3 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < test_data.size(); ++i)
	{	if(i% (test_data.size()/4)==0)
		{
			skiplist_probability_zero_point_two_five.remove(test_data[i]);
			auto end3 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end3 - start3;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_zero_point_two_five2.push_back(load_time_milliseconds_double);
			y_skiplist_probability_zero_point_two_five2.push_back(static_cast<double>(i));
		}
		else
		{
			skiplist_probability_zero_point_two_five.remove(test_data[i]);
		}
	}

	std::vector<double> x_skiplist_probability_zero_point_one_two_five2;
	std::vector<double> y_skiplist_probability_zero_point_one_two_five2;
	auto start4 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < test_data.size(); ++i)
	{	if(i% (test_data.size()/4)==0)
		{
			skiplist_probability_zero_point_one_two_five.remove(test_data[i]);
			auto end4 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end4 - start4;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			x_skiplist_probability_zero_point_one_two_five2.push_back(load_time_milliseconds_double);
			y_skiplist_probability_zero_point_one_two_five2.push_back(static_cast<double>(i));
		}
		else
		{
			skiplist_probability_zero_point_one_two_five.remove(test_data[i]);
		}
	}

	std::vector<double> xs2;
	std::vector<double> ys2;
	auto start2 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < test_data.size(); ++i) //test_data.size()
	{	if(i % (test_data.size()/4)==0)
		{
			r = avl.deleteNode(r, test_data[i]);
			auto end2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> load_time_milliseconds = end2 - start2;
			double load_time_milliseconds_double = load_time_milliseconds.count();
			 //"Load time: " << load_time_milliseconds_double<<std::endl;
			xs2.push_back(load_time_milliseconds_double );
			ys2.push_back(static_cast<double>(i));
		}
		else
		{
			//std::cout <<" ";
			r = avl.deleteNode(r, test_data[i]);
		}
	}
	//avl.printTree(r,0);
	Draw_single_graph(x_skiplist_probability_one_point_five2, y_skiplist_probability_one_point_five2, "SkipList_delete_graph.png",toVector(L"SkipList Delete(p=0.5)"));
	Draw_single_graph(xs2, ys2, "AVL_Tree_delete_graph.png",toVector(L"AVL Tree delete"));
	draw_multi_line_graph(x_skiplist_probability_one_point_five2, y_skiplist_probability_one_point_five2,xs2,ys2,"AVL_Tree_vs_SkipList_delete_graph.png",toVector(L"SkipList(BLUE)(p=0.5) V/S AVL tree(RED) delete"));
	draw_three_line_graph(x_skiplist_probability_one_point_five2, y_skiplist_probability_one_point_five2,x_skiplist_probability_zero_point_two_five2,y_skiplist_probability_zero_point_two_five2,x_skiplist_probability_zero_point_one_two_five2,y_skiplist_probability_zero_point_one_two_five2,"SkipList_vs_SkipList_delete_(probability)_graph.png",toVector(L"SkipList(BLUE)(p=0.5), (RED)(p=0.25), purpel(p=0.125) delete"));
	return;
}
int main()
{
	
	//std::string filename = "Car_Data.csv";
	std::string filename = "Car_Data_small.csv";
    ReadCSV(filename);
	std::shuffle(test_data.begin(), test_data.end(), std::mt19937(std::random_device()()));
	compare_inset_time();
	compare_scearch_time();
	compare_delete_time();
	// for (const auto & test:test_data)
	// {
	// 	std::cout << "ID: " << test <<std::endl;
	// }
    //Print the data
    // for (const auto& car : cars) {
    //     std::cout << "ID: " << car.ID << ", "
    //               << "Brand: " << car.Brand << ", "
    //               << "Model: " << car.Model << ", "
    //               << "Year: " << car.Year << ", "
    //               << "Color: " << car.Color << ", "
    //               << "Mileage: " << car.Mileage << ", "
    //               << "Price: " << car.Price << ", "
    //               << "Condition: " << car.Condition << std::endl;
    // }
}
	

