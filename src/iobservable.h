/**
 * @file iobserver.h
 *
 * @copyright 2020 Zecheng Qian, All rights reserved.
 */
#ifndef SRC_IOBSERVABLE_H_
#define SRC_IOBSERVABLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>

#include "src/iobserver.h"
#include "src/data_structs.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The Subject Interface Class in Observer Pattern.
 *
 * Calls to \ref RegisterObserver function to register an observer.
 *
 * Calls to \ref ClearObservers function to remove all observers.
 *
 * Calls to \ref ClearObservers NotifyObservers to notify all observers.
 */
template <typename T>
class IObservable {
 public:
 /**
  * @brief Register an observer.
  *
  * @param[in] observer Observer to be registered
  */
  void RegisterObserver(IObserver<T> * observer);
 /**
  * @brief Remove all observers for the subject.
  */
  void ClearObservers();
 /**
  * @brief Notify all observer for the changes of the subject.
  *
  * @param[in] info BusData or StopData information, pointer type
  */
  void NotifyObservers(T info);

 private:
  // List of pointers to keep track of all the observers
  std::vector<IObserver<T> *> observers_;
};

/***********************
 * Member Functions
 ***********************/
template <typename T>
void IObservable<T>::RegisterObserver(IObserver<T> * observer) {
  // Push the observer to the observer vector to keep track of
  observers_.push_back(observer);
}

template <typename T>
void IObservable<T>::ClearObservers() {
  // Clear all the existing observers
  std::cout << "Clearing observers vector of size " << observers_.size()
                                                    << std::endl;
  for (int i = 0; i < static_cast<int>(observers_.size()); i++) {
    delete observers_[i];
  }
  observers_.clear();
}

template <typename T>
void IObservable<T>::NotifyObservers(T info) {
  // Notify all the observers about the changes
  for (int i = 0; i < static_cast<int>(observers_.size()); i++) {
    observers_[i]->Notify(info);
  }
}

#endif  // SRC_IOBSERVABLE_H_
