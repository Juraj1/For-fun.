#include <iostream>
#include <memory>

class IVehicle {
public:
  virtual void drive(const std::string &dest) = 0;
  virtual void fill_tank() = 0;
};

class Car : public IVehicle {
public:
  Car() = default;

  virtual void drive(const std::string &dest) override {
    std::cout << "Car driving to: " << dest << std::endl;
  }

  virtual void fill_tank() override {
    std::cout << "Car fuel tank filled" << std::endl;
  }
};

class MotorBike : public IVehicle {
public:
  MotorBike() = default;

  virtual void drive(const std::string &dest) override {
    std::cout << "Motorbike driving to: " << std::endl;
  }

  virtual void fill_tank() override {
    std::cout << "Motorbike fuel tank filled" << std::endl;
  }
};


class IRefuellingDevice {
public:
  virtual void start_refuelling(std::weak_ptr<IVehicle> vehicle) = 0;
};

class GasStation : public IRefuellingDevice {
public:
  GasStation() = default;

  virtual void start_refuelling(std::weak_ptr<IVehicle> vehicle) override {
    std::cout << "Attempting refuel from Gas Station" << std::endl;
    std::shared_ptr<IVehicle> v = vehicle.lock();
    if(v != nullptr) {
      v->fill_tank();
    }
    else {
      std::cout << "Vehicle not available" << std::endl;
    }
  }
};

class FuelCanyster : public IRefuellingDevice {
public:
  FuelCanyster() = default;

  virtual void start_refuelling(std::weak_ptr<IVehicle> vehicle) override {
    std::cout << "Attemptint refuel from Fuel Canyster" << std::endl;
    std::shared_ptr<IVehicle> v = vehicle.lock();
    if(v != nullptr) {
      v->fill_tank();
    }
    else {
      std::cout << "Vehicle not avaiable" << std::endl;
    }
  }
};

int main() {
  
  std::shared_ptr<IVehicle> car = std::make_shared<Car>();
  std::shared_ptr<IVehicle> Bike = std::make_shared<MotorBike>();

  std::shared_ptr<IRefuellingDevice> station = std::make_unique<GasStation>();
  std::shared_ptr<IRefuellingDevice> canyster = std::make_unique<FuelCanyster>();

  car->drive("Gas station");
  station->start_refuelling(car);
  car->drive("Home");
  canyster->start_refuelling(car);

  Bike->drive("Home");
  canyster->start_refuelling(Bike);
  Bike->drive("Gas station");
  station->start_refuelling(Bike);

  return 0;
}
