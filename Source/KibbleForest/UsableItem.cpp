// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableItem.h"

AUsableItem::AUsableItem()
{

}

void AUsableItem::UseItem()
{

}

int AUsableItem::ReturnItemType()
{
	if (IsConsumable) 
	{
		return 0;
	} 
	else if (CanBeThrown) {
		return 1;
	}
	else {
		return 2;
	}
}
