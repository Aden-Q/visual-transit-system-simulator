/**
 * @file mainpage.h
 *
 * @copyright 2020 Zecheng Qian. All rights reserved.
 */

/*! \mainpage Bus Simulator
 *
 * \section intro_sec Introduction
 *
 * This project is a transit simulator around the University of Minnesota. The simulator considers
 * the interactivity of buses, passengers, stops and route. Each route consists of several stops. The 
 * buses load and unload passengers at each stop along their routes. 
 * We provide communication between frontend(JS) and backend(C++) so that
 * all users can run visualization and see the results on a web browser. There are several buttons and scrollbars for
 * user to customize the simulation. Specifically, the users can specify how long they hope to run the
 * simulator, number of time steps between buses for each route. There is a 'Start' button to start the
 * simulation and 'Pause/Resume' button to pause or resume the simulation.
 *
 * You can get the code via the link below. \n
 *
 * https://github.umn.edu/umn-csci-3081-s20/repo-qian0102/tree/master/project \n
 *
 * One thing to note: the link above is private to 3081 stuff only and will not be made public without
 * permission from them.
 *
 * \section design_sec Design
 *
 * \subsection factory_design Factory Pattern
 *
 * By using Factory Pattern, the generation of new objects can be decoupled from the client and makes
 * the code more flexible and scalable. There are two alternative implementations of the Factory Pattern for the Bus class. One is Simple
 * Factory and the other is Abstract Factory.
 * Simple Factory Pattern implements one factory class to create all objects inherited from the same base
 * class. While Abstract Factory Pattern provides an interface for several factory classes, each factory class
 * creates a family of related objects.
 *
 * Simple Factory Diagram:
 *
 * \image html simplefactory.png
 *
 * Explanation: \n
 * 
 * As the diagram above shows, in the Client we need to instantiate a 'MobileFactory' object. Whenever the
 * Client needs to create an 'IMobile' object, it simply needs to invoke 'MobileFactory' object's 'GetMobile'
 * method to create one.
 *
 * \image html abstractfactory.png
 *
 * Explanation: \n
 *
 * As the diagram above shows, in the Client we follow the same logic as the Simple Factory Pattern. The difference
 * is that this time we have two families of class, '3GMobile' and '4GMobile', and each family have some related objects.
 * The 'IMobileFactory' specifies a factory interface implemented by two concrete factories classes. The factory interface
 * requires all derived factory classes to implement two methods. One is to create Nokia mobiles and the other is to
 * create Apple mobiles. Two concrete factories create '3GMobile' and '4GMobile' objects respectively.
 *
 * \subsection bus_factory_design Bus Factory Pattern
 *
 * The Factory Pattern I choose to implement for the Bus class is Simply Factory Pattern. There are three types of classes
 * which are SmallBus, RegularBus, and LargeBus. They are all inherited from Bus class and have different capacities and 'Report' methods.
 * Their capacities are 30, 60 and 90 respectively. One concrete factory class called BusFactory will generate different types of
 * buses based on the input parameter 'capacity'.
 * 
 * One pro of Simple Factory Pattern is that it is easy to design and implement. In this schema, for Bus class, only one factory class
 * is needed, which is BusFactory. Whenever a new bus needs to be instantiated, the bus factory object takes parameters and decided which bus to create based on
 * the parameters. However, in the schema of Abstract Factory Pattern, differents factories are needed to create different types of classes
 * which is more complex. So complexity is one con of Abstract Factory Pattern and sometimes reduces the readability.
 *
 * One con of Simple Factory Pattern is that it is not easy to extend compared to Abstract Factory Pattern. Think about the situation when
 * we want to add some subtypes of SmallBus for the factory to create, such as SmallBlueBus and SmallRedBus. Then by Simple Factory Pattern approach,
 * we have to implement the logic in BusFactory to tell which SmallBus will be created. That will certainly clutter the BusFactory. However, by Abstract
 * Factory Pattern approach, we only need to modify the factory which creates SmallBus object and does not need to do anything with the other two types
 * of buses. So one con of Abstract Factory Pattern is that it is easy to extend.
 *
 * \subsection domain_structure Domain Element Structure
 *
 * The transit simulation system is implemented with JavaScript frontend (Client) and C++ backend (Server). The frontend and backend communicate through a socket
 * on a port. When the user clicks on a button, the signal will be sent to a webserver and some regisited callbacks from the server will be invoked to make a response.
 * Currently there are two buttons, 'Start' and 'Pause/Resume' and several scroll bars. After running the server in the backend, the user can press on the 'Start' button
 * to let the simulation begin. The user can also click on the 'Pause/Resume' button to pause or resume the simulation. The routes and stops are instantiated via a configuration
 * file in 'config/config.txt'. The user can also customize it if he wants.
 *
 * \subsection observer_design Designing and Implementing the Observer Pattern
 * 
 * \subsubsection intro_observer Introduction to Observer Pattern
 * Observer Pattern is a design pattern that defines a one-to-many relationship so that all the dependents are notified if the observed object changes its state.
 * This scheme is proposed to provide a loosely coupled relation between objects that interact with each other.
 * 
 * Observer Pattern UML Diagram:
 *
 * \image html observer_pattern_diagram.png
 *
 * Explanation: \n
 * 
 * Observer and Subject are two interface classes. The Observer keeps track of the data from the Subject. It has a notify() method so that whenever changes are made to the Subject,
 * all observers will be notified about the changes. The Subject maintains a collection of observers who want to observe it. The Subject class has three methods: registerObserver(observer)
 * which adds an observer to the observer collection, unregisterObserver(observer) which removes an observer from the collection and notifyObservers() which defines actions to take when the data is
 * changed within the Subject and Observer wants to know the new data. ConcreteObserverA and ConcreteObserverB are derived from Observer interface and they are actual observers. 
 * Similarly, actual subjects should also implement the Subject interface.
 * 
 * \subsubsection implement_observer Implementing Bus Observer Pattern
 *
 * Bus Observer Pattern UML Diagram: \n
 *
 * \image html bus_observer.png
 *
 * Explanation: \n
 *
 * In this project, I implement Observer Pattern for the Bus class. The name, position(longitude and latitude) and the number of passengers on it are the data to be observed as a bus proceeds along a route.
 * Specifically, the Bus class implement Subject interface and the BusWebObserver class implement Observer interface. If the data for a bus is updated, then the registered observer will be notified about
 * the change and the information will be sent to the browser and displayed on the web page.
 * 
 * To implement the Observer Pattern, first we need to add two classes IObservable and IObserver. The IObservable class needs to implement three methods: RegisterObserver(IObserver *) which adds an observer
 * to a bus, ClearObservers() which clears all observers for a bus and NotifyObservers(BusData *) which notifies observers about the changes. The IObserver class needs to implement a Notify(BusData *) method
 * to define the actions to take when changes to a bus are made.
 * 
 * For the Bus class, first it needs to inherit from the ISubject interface. And a NotifyObservers(BusData *) method is added to the bottom of Bus::Update() method since that's the place where BusData gets updated
 * for a bus. The BusWebObserver class implements the Notify(BusData *) to keep track of the updated information.
 * 
 * For the web end, the logic behind is similar, a listener command is an observer for mouse events on the web page, it is notified when changes are detected. The VisualizationSimulator implements two methods,
 * ClearListeners() which removes all observers and AddListener(string *, IObserver *) method which adds an observer to a subject.
 * 
 * Challenges and difficulties: Overall the Observer Pattern is easy to implement with the Bus class. The key point is to decide where to put NotifyObservers(BusData *) in Bus class. My advice is that we
 * understand the logic of all Bus methods first, then understand how Observer Pattern works. I learn Observer Pattern from online resources (the link is provided below) and some code examples.
 * As long as we understand them correctly, everything seems to be very straightforward.
 *
 * https://www.geeksforgeeks.org/observer-pattern-set-1-introduction/
 *
 * \subsection decorator_design Designing and Implementing the Decorator Pattern
 * 
 * \subsubsection intro_observer Introduction to Observer Pattern
 * Decorator Pattern is a design pattern that provides a flexible mechanism for extending the functionality of a certain class. It is an alternative to subclassing. However, subclassing extends functionality at
 * at compile time, while Decorator Pattern extends functionality at runtime. Decorator Pattern offers a way to extend functionality on demand. Specifically, we can instantiate a very simple class at first,
 * then every time it needs new features, we can use the decorator classes to add functionality.
 * 
 * Decorator Pattern UML Diagram:
 *
 * \image html decorator_pattern_diagram.jpg
 *
 * Explanation: \n
 * 
 * The above UML diagram shows the main structure for the Decorator Pattern. The Component class is an abstract interface that defines operations for both the class we want to decorate and the decorator class.
 * Both the Concrete Component class and the Decorator class extends the Component interface. Concrete Decorator extends the Decorator classes and can be used for adding different functionality.
 * 
 * \subsubsection implement_decorator Implementing Bus Decorator Pattern
 *
 * Bus Observer Pattern UML Diagram: \n
 *
 * \image html bus_decorator.png
 *
 * Explanation: \n
 *
 * In this project, I implemented Decorator Pattern for the Bus class for two purposes:
 *
 * 1. Change the bus color depending on whether it is on the inbound or outbound route. \n
 * 2. Change the bus color intensity depending on the number of passengers on the bus. \n
 *
 * 
 * Because the Bus class inherits IObservable class in the Observer Pattern which I implemented previously, first I implement an IBus class that inherits IObservable and define the interface. There are
 * three methods named UpdateBusData(), SetColor() and SetIntensity(int) respectively. The latter two methods are for different decorating purposes. And the first one is used for convenience and wrap up
 * the decorating code. The Bus class is the concrete class which we want to decorate and we already have it in the previous iterations. We simply need several setter methods to update its color information.
 * Different decorator classes are implemented by inheritance. The BusDecorator class is the base one. It implements the UpdateBusData() method to set a default color (Maroon) and color intensity (maximum) for a concrete bus.
 * It is used whenever a new bus is generated. Then three concrete decorator classes inherit the base decorator class and perform different decorator operations. As their names suggest, BusColorMaroonDecorator is used for changing the bus color to Maroon,
 * BusColorGoldDecorator is used to change the bus color to Gold, and BusIntensityDecorator is used to change the Bus color intensity. The BusColorMaroonDecorator and BusColorGoldDecorator are used whenever the bus data gets updated.
 * Then we check whether the bus is on the inbound or outbound route to decide which decorator class to use. The BusIntensityDecorator is used when the bus loads or unloads passengers because
 * the number of passengers on the bus will change only at that time. It then will check the number of passengers on the bus and calculate a proper intensity to set. Following is the formula I use to calculate the intensity:
 *
 * alpha = max(255, 100 + 15 * num_passenger_on_bus)
 *
 * Pros: This design is open for extension and close for modification, It provides a more flexible way to extend functionality for the Bus class. Each time we want to add new colors or modify the way to change intensity,
 * we can finish it by adding new concrete decorator classes and don't need to modify the Bus code. So it provides low coupling between the classes. It also provides high cohesion because everything is done within a concrete decorator class.
 *
 * Cons: It may be complicated if we want multi-layer decoration, in that case, we have to keep track of the order of the decorations. Although in the above case, the decoration order doesn't matter, in some other cases, the order does matter.
 *
 * \subsubsection alternative_decorator Alternative Design for Bus Decorator Pattern
 *
 * This is an alternative design that I don't implement. Here's the diagram for this design from Prof. Wrenn's lecture slide:
 *
 * \image html bus_decorator_alternative.png
 *
 * Explanation: \n
 *
 * We can see this design is very similar to the previous one which I implement for this project. The only difference is that this design integrates the functionality for changing color and intensity into one class named BusDecorator. (The previous design
 * separate different decorators by using inheritance.) \n
 *
 *
 * Pros: This design provides a more convenient way to decorate the Bus class since everything is done in a single class. So it provides high cohesion. It also provides low coupling between the decorator class and the class to be decorated.
 * Every time we want to add new functionality for decoration, we don't need to modify many codes within the Bus class, instead, we only need to modify the BusDecorator class. It is open for extension.
 *
 * Cons: This design is not close for modification. Specifically, every time we want to add new functionality, we have to modify the BusDecorator class, for example, if we want a new color, we have to modify the code in BusDecorator to
 * incorporate that information. In our previous design, we don't need to modify the existing code. Instead, we can extend functionality by adding new classes.
 *
 * \subsubsection difficulties_tips Difficulties and Tips
 *
 * For me everything is straight once I understand each design pattern. And the most difficult part for me is how to change color intensity. Since I have to figure out a proper way to get the BusData and modify it based on the number of passengers.
 * It seems that there isn't such a convenient way with low coupling to add this new feature because the decorator has to access some data within the Bus class. And the way I address this problem is by adding new setters.
 * The most useful resource for me to understand the design pattern is Prof. Wrenn's lecture and the provided reading materials. The links below help me a lot in implementing the design pattern:
 *
 * https://www.geeksforgeeks.org/the-decorator-pattern-set-2-introduction-and-design/?ref=lbp \n
 * https://www.geeksforgeeks.org/decorator-pattern-set-3-coding-the-design/?ref=lbp
 *
 * \section install_sec Running The Code
 *
 * \subsection config Configuration
 *
 * Here are several things to be done to configure the project.
 *
 * 1. Clone the code repository into your local machine. \n
 * 2. Make sure "g++" and "make" tools are installed on your local machine. \n
 *
 * \subsection compile_exec Compiling and Executing
 *
 * Compiling:
 *
 * 1. Change directory into "project/src". \n
 * 2. Type 'make' in the terminal. \n
 *
 * Executing:
 * 
 * 1. Change directory into "project". \n
 * 2. Type './build/bin/vis_sim 8081' \n
 * 3. Open your browser and navigate to the following address: http://127.0.0.1:8081/web_graphics/project.html \n
 *
 * 
 * The number 8001 specified above is the port number. If this port is occupied by other processes in your local machine.
 * Feel free to change it to other numbers above 8000.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

#endif  // SRC_MAINPAGE_H_

