#pragma once

class Resource {

private:
    int kind;
    int amountOfResources;

public:
    Resource(int kind);

    int getKindResourceCode();
    int getCurrentAmountResources();
    void setCurrentAmountResources(int newAmount);
    void addOneToCurrentAmountResources();
    void TakeOneResourceTone();
};

