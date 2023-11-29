#include "MapChip.h"

MapChip::MapChip() {

}

MapChip::~MapChip() {
	delete model_;
}

void MapChip::Init() {
	model_ = new Model;
}

void MapChip::Updata() {

}

Vector3 MapChip::GetWorldPosition(){
	return model_->transform.translate;
}
