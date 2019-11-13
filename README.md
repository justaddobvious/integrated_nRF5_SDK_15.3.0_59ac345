# integrated\_nRF5\_SDK\_15.3.0\_59ac345
nRF5\_SDK\_15.3.0\_59ac345 examples with obvious integrated. Currently, only the PCA10040 development kit with SoftDevice S132 and an ARM GCC toolchain are supported. Note that the following guide was developed using a macOS environment. To test the non-Obvious functionality of the examples, please refer to the [Nordic Semiconductor Infocentre](https://infocenter.nordicsemi.com/topic/com.nordic.infocenter.sdk5.v15.3.0/examples_ble_peripheral.html).

## Step-By-Step Integration Guide
1. Clone this repository with the command ```git clone https://github.com/justaddobvious/integrated_nRF5_SDK_15.3.0_59ac345.git```  
and initialize submodules using the command ```git submodule --init```
2. Create a new Obvious portal on [our website](https://portal.obvious.xyz/create).
3. Once logged in, create a new product by clicking "Add" in the top-right corner of the portal's "Products" tab. 
  * For these examples, name your product "Example Product"
  * The feature region size should be 4096.
4. Click on your product, and create a new feature by clicking "Add" in the top-right corner of the product's "Features" tab.
  * For these examples, name your feature "Feature LED 4". If you wish to evaluate the ble\_app\_uart example, name your feature "Feature UART".
  * Using the drop-down list, select "Purchasable" as the option for how the feature is to be delivered.
  * Toggle the "Feature Status" button to the "on" position.
5. Add the feature to your product's catalog.
  * Navigate to the portal's "Sales" tab, and select the "Catalog" option.
  * Select your product, and then click the "Add" button in the top-right corner of the page.
  * Select "Individual" as the type of catalog item from the first drop-down menu, and select the name of your feature from the second drop-down menu.
  * Give your catalog entry a name, description, SKU, and a price. Enter image and thumbnail URLs if you wish. Then, click the "Add Individual Entry" button at the bottom of the form.
6. Build and download the embedded library.
  * Select the portal's "Products" tab, click on your product, and then select the "Firmware" tab on the left side of the page.
  * Select the "Library" option, and click "Create" in the top-right corner of the page.
  * Select SoftDevice S132, and choose version 6.1.1 from the drop-down list.
  * Select NRF52832\_XXAA as your chip.
  * Set Ocelot Flash Start to 0x7B000, and Ocelot Reset Safe Ram Start to 0x2000FFE0
  * Click "Generate SDK library".
  * Once the build finishes, click "Download" on the card displaying your build's details and extract the .zip file to a location of your choosing.
7. Navigate to the portal's "Tools" tab, select the "Product File Generators" option, and click "Embedded" on the right side of the page to download a file that contains information concerning your products and features called "ocelot\_feature.h".
8. Copy the files "ocelot.h" and "libocelot.ld" from the SDK library folder extracted in step 6 as well as "ocelot\_feature.h" to $(INSTALL\_ROOT)/ocelot/include/
9. Copy "libocelot.a" from the library folder to $(INSTALL\_ROOT)/ocelot/lib/
10. Navigate to the Makefile of the example you wish to evaluate. For example, if you would like to evaluate the ble\_app\_blinky example, navigate to $(INSTALL\_ROOT)/obvious\_examples/ble\_peripheral/ble\_app\_blinky/pca10040/s132/armgcc
11. Set the GNU\_INSTALL\_ROOT environment variable to /usr/local/gcc-arm-none-eabi-7-2018-q2-update/bin/ and ensure that ARM GCC 7-2018-q2-update is indeed located in the aforementioned location.
12. Build the example by entering the ```make``` command.
13. Program the example onto your development kit by entering ```make erase```, ```make flash_softdevice```, and then ```make flash```
14. Back in the portal, select your product and navigate to the "Keys" page. Then, make note of your 16-byte product key. This key must be flashed onto your development board at address 0x7C000. On *nix machines, this can be accomplished by first entering the command ```echo 'PRODUCT_KEY' | xxd -r -p > product_key.bin```. Then, connect to your development kit with the JLink Commander utility and send it the command ```loadbin product_key.bin, 0x7C000```. At this point, the example can be tested with the Obvious Discover app!
15. In the Obvious Discover app, select your device from the scan menu. You may wish to filter the list by tapping the three dots on the top-right side of the screen.
16. Once your device has been selected, it will be provisioned automatically, and a feature update will occur. Notice that LED 4 on the development kit is not on. If you are evaluating the ble\_app\_uart example, notice that messages will be printed to the terminal backwards.
17. Navigate to the app's checkout tab, select your feature, and tap "Checkout". To purchase the feature, use the test Visa number 4242424242424242 with expiry 10/30 and CVV 123.
18. Once the purchase is complete, notice that LED 4 on the development board is turned on. If you are evaluating the ble\_app\_uart example, notice that messages are now printed to the terminal properly.
19. Return to the device menu and experiment with toggling the feature that was just purchased by tapping the button at the bottom of the card titled with the feature's name. In this way, the purchased feature can easily be activated and deactivated on the device!

  
