#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Input.h"
#include "MouseHandler.h"
#include "DrawingUtils.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "Vehicle.h"
#include "CarMovementStrategy.h"
#include "TruckMovementStrategy.h"
#include "HelicopterMovementStrategy.h"
#include "PersonMovementStrategy.h"

using namespace std;
using namespace cv;

const string BASE_PATH_TILES = "D:/Users/User/Desktop/TILES/TILES/";
const string BASE_PATH_VEHICLES = "D:/Users/User/Desktop/VEHICLES/VEHICLES/";
const string BASE_PATH_PEOPLE = "D:/Users/User/Desktop/People/WALKING PERSON 2/";

Rect selection;
bool selecting = false;
bool selected = false;
Mat screen;

void onMouse(int event, int x, int y, int, void* param) {
    MouseHandler::onMouse(event, x, y, param);
}

int main() {
    Input i;
    vector<vector<string>> vec = i.parse_and_store();

    unordered_map<string, string> imagesNamesTails = {
        {"1", "tile_ground.png"},
        {"2", "tile_water.png"},
        {"3", "tile_forest.png"},
        {"4", "tile_field.png"},
        {"5", "tile_iron_mine.png"},
        {"6", "tile_blocks_mine.png"},
        {"7", "tile_road.png"}
    };

    Mat sampleImage = imread(BASE_PATH_TILES + imagesNamesTails["1"]);
    if (sampleImage.empty()) {
        cerr << "Error loading sample image!" << endl;
        return -1;
    }

    int tileWidth = sampleImage.cols;
    int tileHeight = sampleImage.rows;

    screen = *(new Mat(vec.size() * tileHeight, vec[0].size() * tileWidth, sampleImage.type()));
    for (int row = 0; row < vec.size(); ++row) {
        for (int col = 0; col < vec[0].size(); ++col) {
            Mat img = imread(BASE_PATH_TILES + imagesNamesTails[vec[row][col]]);
            if (!img.empty()) {
                DrawingUtils::drawGrid(img);
                Rect roi(col * tileWidth, row * tileHeight, tileWidth, tileHeight);
                img.copyTo(screen(roi));
            }
            else {
                cerr << "Error loading tile image at row " << row << " col " << col << endl;
            }
        }
    }

    unordered_map<int, string> imagesNamesCars = {
        {1, "Audi.png"},
        {2, "Black_viper.png"},
        {3, "Car.png"},
        {4, "Police.png"},
        {5, "taxi.png"}
    };

    unordered_map<int, string> imagesNamesTrucks = {
        {1, "Ambulance.png"},
        {2, "Mini_truck.png"},
        {3, "truck.png"},
        {4, "Mini_van.png"}
    };

    unordered_map<int, string> imagesNamesPeople = {
        {1, "sprite_1.png"},
        {2, "sprite_2.png"},
        {3, "sprite_3.png"},
        {4, "sprite_4.png"},
        {5, "sprite_5.png"}
    };

    string imageNameHelicopter = "helicopter.png";

    vector<std::shared_ptr<Vehicle>> vehicles;

    for (const auto& startCommand : i.start) {
        int x = (std::stoi(startCommand->arguments[1]) - 1) * 10;
        int y = (std::stoi(startCommand->arguments[2]) - 1) * 10;

        std::shared_ptr<MovementStrategy> strategy;

        switch (startCommand->commandType) {
        case CommandType::MANUFACTURE:
            if (startCommand->arguments[0] == "Car") {
                strategy = std::make_shared<CarMovementStrategy>();
                vehicles.push_back(std::make_shared<Vehicle>(BASE_PATH_VEHICLES + imagesNamesCars[std::stoi(startCommand->arguments[1])], x, y, strategy));
            }
            else if (startCommand->arguments[0] == "Truck") {
                strategy = std::make_shared<TruckMovementStrategy>();
                vehicles.push_back(std::make_shared<Vehicle>(BASE_PATH_VEHICLES + imagesNamesTrucks[std::stoi(startCommand->arguments[1])], x, y, strategy));
            }
            else if (startCommand->arguments[0] == "Helicopter") {
                strategy = std::make_shared<HelicopterMovementStrategy>();
                vehicles.push_back(std::make_shared<Vehicle>(BASE_PATH_VEHICLES + imageNameHelicopter, x, y, strategy));
            }
            break;

        case CommandType::PEOPLE:
            strategy = std::make_shared<PersonMovementStrategy>();
            vehicles.push_back(std::make_shared<Vehicle>(BASE_PATH_PEOPLE + imagesNamesPeople[std::stoi(startCommand->arguments[1])], x, y, strategy));
            break;

        default:
            break;
        }
    }


    int imageIndex = 0;

    while (true) {
        Mat displayImage = screen.clone();
        for (auto& vehicle : vehicles) {
            vehicle->move();
            Mat vehicleImage = imread(vehicle->getImageName());
            if (vehicleImage.empty()) {
                cerr << "Error loading image for vehicle!" << endl;
                continue;
            }
            DrawingUtils::overlayImage(displayImage, vehicleImage, vehicle->getX(), vehicle->getY());
        }

        imageIndex = (imageIndex + 1) % 5;
        namedWindow("Image");
        setMouseCallback("Image", onMouse, &displayImage);
        imshow("Image", displayImage);
        if (waitKey(100) == 27) break;
    }

    return 0;
}
