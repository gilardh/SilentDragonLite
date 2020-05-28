#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "precompiled.h"
#include "contactmodel.h"
#include "FileSystem/FileSystem.h"

class MainWindow;

class AddressBookModel : public QAbstractTableModel {

public:
    AddressBookModel(QTableView* parent);
    ~AddressBookModel();

    void                    addNewLabel(QString label, QString address, QString myAddr, QString cid, QString avatar);
    void updateUi();
    void                    removeItemAt(int row);
    //QPair<QString, QString> itemAt(int row);
    ContactItem itemAt(int row);

    int      rowCount(const QModelIndex &parent) const;
    int      columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  

private:
    void loadData();
    void saveData();

    QTableView* parent;
    //QList<QPair<QString, QString>> labels;
    QList<ContactItem> labels;
    QStringList headers;  
    
};

class AddressBook {
public:    
    // Method that opens the AddressBook dialog window. 
    static void open(MainWindow* parent, QLineEdit* target = nullptr);

    static AddressBook* getInstance(); 
    static QString addLabelToAddress(QString addr);
    static QString addressFromAddressLabel(const QString& lblAddr);

    // Add a new address/label to the database
    void addAddressLabel(QString label, QString address, QString myAddr, QString cid, QString avatar);

    // Remove a new address/label from the database
    void removeAddressLabel(QString label, QString address, QString myAddr, QString cid, QString avatar);

    // Update a label/address
    void updateLabel(QString oldlabel, QString address, QString newlabel);

    // Read all addresses
    const QList<ContactItem>& getAllAddressLabels();

    // Get an address's first label
    QString getLabelForAddress(QString address);
    // Get a Label's address
    QString getAddressForLabel(QString label);

    QString get_avatar_name();
    void set_avatar_name(QString avatar_name);

    

    
    
    

    

private:
    AddressBook();

    void readFromStorage();
    void writeToStorage();

    QString writeableFile();
    QList<ContactItem> allLabels;
    

    static AddressBook* instance;
};

#endif // ADDRESSBOOK_H