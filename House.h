#pragma once

#include <stdint.h>
#include <array>
#include<memory>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:
	static constexpr size_t height_h = 7;
	static constexpr size_t width_h = 14;

	explicit House(const std::array<char, width_h * height_h>& look);

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

private:

	char look[height_h][width_h];
	const uint16_t score = 40;
};

class HouseBuilderA {
public:

	HouseBuilderA& createTriangleRoof()& {
		current_look = {
		"      ##      "
		"   ##    ##   "
		" ##        ## "
		"##############"
		" #          # "
		" #          # "
		" ############"
		};
		return *this;
	}

	HouseBuilderA& createSquareRoof()& {
		current_look = {
		"              "
		"              "
		" ############ "
		" #          # "
		" #          # "
		" #          # "
		" ############"
		};
		return *this;
	}

	std::unique_ptr<House> buildHouse() const {
		return std::make_unique<House>(current_look);
	}

private:
	std::array<char, House::width_h * House::height_h> current_look = {
		"              "
		"  ##########  "
		"##          ##"
		"##############"
		"#            #"
		"#            #"
		" ############"
	};

	char cur_look[House::height_h][House::width_h];


};

class HouseDirector
{
public:
	HouseDirector() : builder{ std::make_unique<HouseBuilderA>() } {}

	std::unique_ptr<House> buildWithSquareRoof() const {
		return builder->createSquareRoof().buildHouse();
	}

	std::unique_ptr<House> buildWithTriangleRoof() const {
		return builder->createTriangleRoof().buildHouse();
	}

	std::unique_ptr<House> buildWithDefaultRoof() const {
		return builder->buildHouse();
	}


private:
	std::unique_ptr<HouseBuilderA> builder;
};
