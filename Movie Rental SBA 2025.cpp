
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define AMT 25 //To display all the movies from the text file 
#define CARTAMT 25 //The maximum amount of movies that the cart can hold 

struct video 
{
    int id;
    char title[40];
    float price;
};

struct cart_movie 
{
    int id;
    char title[40];
    float price;
};

// Function prototypes
void displaymenu();
void searchname(struct video menu[], struct cart_movie cart[], int* cart_size);
void viewcart(struct cart_movie cart[], int* cart_size);
void profilelogin();
void movieprice_range(struct video menu[], struct cart_movie cart[], int* cart_size);
void handle_checkout(struct cart_movie cart[], int* cart_size);
void remove_from_cart(struct cart_movie cart[], int* cart_size);

// Display main menu
void displaymenu() 
{
    printf("\n\tWELCOME TO\n");
    printf("***MARVELOUS MOVIE RENTALS***\n");
    printf("-----------------------------\n");
    printf("1. Search Price Range\n");
    printf("2. Search Title\n");
    printf("3. View Cart\n");
    printf("4. Total Cart & Checkout\n");
    printf("5. Exit\n");
    printf("-----------------------------\n");
}

// Movie search by title
void searchname(struct video menu[], struct cart_movie cart[], int* cart_size) 
{
    int i, found;
    char movitem[30];
    int add_more = 1;

    do 
	{
      found = 0;
      printf("Please enter the movie you would like to search: ");
      scanf(" %29[^\n]s", movitem);

    for(i = 0; i < AMT; i++) 
	{
        if(stricmp(movitem, menu[i].title) == 0) 
		{
            printf("Price: $%.2f\n", menu[i].price);
            printf("Add movie to cart? Y/N: ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y') 
			{
                cart[*cart_size].id = menu[i].id;
                cart[*cart_size].price = menu[i].price;
                strcpy(cart[*cart_size].title, menu[i].title);
                (*cart_size)++;
                printf("Movie added to cart.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) 
	 {
        printf("Movie not found!\n");
     }

     printf("Search another movie? Y/N: ");
     char more_items;
     scanf(" %c", &more_items);
     if (more_items == 'N' || more_items == 'n') 
	 {
        add_more = 0;
        printf("Press 'Enter' to return to main menu. ");
        while(getchar() != '\n'); 
        getchar(); 
     }
    }   while(add_more);	
}

// View cart with checkout & edit options
void viewcart(struct cart_movie cart[], int* cart_size) 
{
    if (*cart_size == 0) 
	{
        printf("Your cart is empty.\n");
        printf("Press 'Enter' to return to main menu. ");
        while(getchar() != '\n');
        getchar();
        return;
    }

    printf("\nMovies in Cart:\n");
    float total = 0;
    for(int i = 0; i < *cart_size; i++) 
	{
        printf("%d. %s  $%.2f\n", i+1, cart[i].title, cart[i].price);
        total += cart[i].price;
    }
    printf("TOTAL: $%.2f\n", total);

    printf("\n1. Proceed to Checkout\n2. Remove Item(s)\n3. Continue Shopping\n");
    printf("Enter choice: ");
    int choice;
    scanf("%d", &choice);

    switch(choice) 
	{
        case 1:
            handle_checkout(cart, cart_size);
            break;
        case 2:
            remove_from_cart(cart, cart_size);
            viewcart(cart, cart_size); 
            break;
        default:
            break;
    }
}


void profilelogin() 
{

    char username[30];
    int password;

    // Asks user to enter a username
    printf("\nEnter username: ");
    scanf("%29s", username);
      
    do 
	{
        printf("Enter 4-digit password: ");
        scanf("%d", &password);
         if(password < 1000 || password > 9999)
         {
         	printf("INVALID PASSWORD.\nEnter a valid 4-digit password: ");
         	scanf("%d", &password);
		 }
    } 
	while (password < 1000 || password > 9999);
	
	printf("-----------------------------\n");
	printf("Username: %s\n", username);
 	printf("Password: %d\n", password);

}

// Price range search
void movieprice_range(struct video menu[], struct cart_movie cart[], int* cart_size) {
    float min, max;
    printf("Enter minimum price: ");
    scanf("%f", &min);
    printf("Enter maximum price: ");
    scanf("%f", &max);

    int found = 0;
    for(int i = 0; i < AMT; i++) 
	{
        if(menu[i].price >= min && menu[i].price <= max) 
		{
            printf("%d. %s  $%.2f\n", i+1, menu[i].title, menu[i].price);
            printf("Add to cart? Y/N: ");
            char choice;
            scanf(" %c", &choice);
            if(toupper(choice) == 'Y') 
			{
                cart[*cart_size].id = menu[i].id;
                cart[*cart_size].price = menu[i].price;
                strcpy(cart[*cart_size].title, menu[i].title);
                (*cart_size)++;
                printf("Movie added to cart.\n");
               
            }
            found = 1;
        }
    }

    if(!found) 
	{
        printf("No movies found in this price range!\n");
    }

    printf("Press 'Enter' to continue. ");
    while(getchar() != '\n');
    getchar();
}

// Checkout process
void handle_checkout(struct cart_movie cart[], int* cart_size) 
{

	if(*cart_size == 0) 
	{
        printf("Your cart is empty!\n");
        return;
    }

    float total = 0;
    printf("-----------------------------\n");
    printf("Thank you for shopping with us!\n");
    printf("Here is your receipt!\n");
    printf("-----------------------------\n");
   
    for(int i = 0; i < *cart_size; i++) 
	{
        printf("%s\t$%.2f\n", cart[i].title, cart[i].price);
        total += cart[i].price;
    }

    float tax = total * 0.10;
    printf("-----------------------------\n");
    printf("\nSUBTOTAL: $%.2f", total);
    printf("\nTAX (10%%): $%.2f", tax);
    printf("\nTOTAL: $%.2f\n", total + tax);
    printf("-----------------------------\n");
    
    if (*cart_size == CARTAMT) //25 movies to fill cart
    {
    	printf("Your cart is full.");
    	return;
	}
	
	if (*cart_size >=5 && *cart_size <10)
	{
		printf("You are eligible for a 5%% discount!\n");
		printf("-----------------------------\n");
		float discount= (0.05*total);
		float after_discount= total-discount;
		printf("TOTAL AFTER DISCOUNT: $%.2f", after_discount + tax);
	}
	
	if (*cart_size >=10 && *cart_size <=25) 
	{
		printf("You are eligible for a 10%% discount!\n");
		printf("-----------------------------\n");
		float discount= 0.1*total;
		float after_discount= total-discount;
		printf("TOTAL AFTER DISCOUNT: $%.2f", after_discount + tax);
	}

    printf("\n-----------------------------\n");
	printf("\nDelivery option (additional $15)\n1. Pickup\n2. Delivery\nEnter choice: ");
    int choice;
    scanf("%d", &choice);
    
  if(choice == 2) 
 {
    char delivery_location[250];
    char confirm_delivery[250];
    int delivery_fee = 15;
    int c; // For clearing input buffer
    
    printf("\nThank you for choosing delivery.\n");
    printf("-----------------------------\n");
    printf("Please enter the delivery location.\n");
    scanf(" %249[^\n]s", delivery_location);
    // Clear input buffer
    while ((c = getchar()) != '\n' && c != EOF);

    // Confirm delivery location
    do 
	{
        printf("-----------------------------\n");
        printf("Confirm Delivery Location.\n");
        scanf(" %249[^\n]s", confirm_delivery);
        // Clear input buffer
        while ((c = getchar()) != '\n' && c != EOF);

        if (strcmp(delivery_location, confirm_delivery) != 0) 
		{
            printf("Delivery Location not confirmed.\nPlease enter the correct location.\n");
        }
    } 
	while (strcmp(delivery_location, confirm_delivery) != 0);

    printf("-----------------------------\n");
    printf("Delivery Location Successfully Confirmed!\n");
    printf("The delivery location is %s.\n\n", confirm_delivery);

    printf("Your movie(s) will be delivered within 24 hours to '%s'.\nAn extra $15 will be added to your total.\n", confirm_delivery);
    
    if (*cart_size >=5 && *cart_size <10)
    {
    	float discount= (0.05*total);
		float after_discount= total-discount;
		printf("TOTAL WITH DELIVERY: $%.2f\n", after_discount + delivery_fee + tax );
	}
	if (*cart_size >=10 && *cart_size <=25)
	{
		float discount= 0.1*total;
		float after_discount= total-discount;
		printf("TOTAL WITH DELIVERY: $%.2f\n", after_discount + delivery_fee + tax );
	}
     

    *cart_size = 0; // Clear cart
    printf("\nThank you for your purchase. Have a MARVELOUS day!\n");
    exit(0);
  }
else 
  {
    *cart_size = 0; // Clear cart
    printf("\nThank you for choosing pickup.\nYour movie(s) will be available for pickup in an hour.\n");
    printf("\nThank you for your purchase. Have a MARVELOUS day!\n");
    exit(0);
   }
}

// Remove item from cart
void remove_from_cart(struct cart_movie cart[], int* cart_size) 
 {
    if(*cart_size == 0) 
	return;

    printf("Enter item number to remove: ");
    int index;
    scanf("%d", &index);
    
    if(index < 1 || index > *cart_size) 
	{
        printf("Invalid item number!\n");
        return;
    }

    for(int i = index-1; i < *cart_size-1; i++) 
	{
        cart[i] = cart[i+1];
    }
    
    (*cart_size)--;  //to remove the selected item from cart
    printf("Item removed successfully.\n");
 }


int main() 
{
   	struct video menu[AMT]={0};
    struct cart_movie cart[AMT];
    char filename[100]= "movielist.txt";
  	int choice, i, found; 
  	char username[30];
  	float money; 
  	float total, subtotal, tax, discount;
  	char delivery_location[250];
    int cart_size = 0;
    
    // To load movies from text file
    FILE *file1 = fopen("movielist.txt", "r");
    if(file1) 
	{
        for(int i = 0; i < AMT; i++) 
		{
            fscanf(file1, "%d %f %[^\n]", &menu[i].id, &menu[i].price, menu[i].title);
        }
        fclose(file1);
    }
    
    	for(i=0; i<AMT && !feof(file1); i++) //Reads all the menu items
	{
		
		fscanf(file1, " %d",&menu[i].id );
		fgetc(file1);
		fscanf(file1, " %f",& menu[i].price);
		fgetc(file1);
		fscanf(file1, " %[^\n]s",&menu[i].title);
		fgetc(file1);
		printf(" %d $%.2f %s\n",menu[i].id,menu[i].price , menu[i].title);
	}
	fclose(file1);

    profilelogin();
    
    do 
	{
        displaymenu();
        printf("Please enter choice: ");
        scanf("%d", &choice);

        switch(choice) 
		{
            case 1:
                movieprice_range(menu, cart, &cart_size);
                break;
            case 2:
                searchname(menu, cart, &cart_size);
                break;
            case 3:
                viewcart(cart, &cart_size);
                break;
            case 4:
                handle_checkout(cart, &cart_size);
                break;
            case 5:
                printf("Thank you for using our software.\n\n\t HAVE \n\t   A \n       MARVELOUS \n\t  DAY\n\t FROM\n");
                printf("***MARVELOUS MOVIE RENTALS***\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    } while(1);

    return 0;
}
