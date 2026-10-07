const foods = [
    {
        id: 1,
        name: "Margherita Pizza",
        category: "Pizza",
        price: 249,
        emoji: "🍕",
        description: "Fresh mozzarella, tomato & basil"
    },

    {
        id: 2,
        name: "Farmhouse Pizza",
        category: "Pizza",
        price: 299,
        emoji: "🍕",
        description: "Loaded with fresh vegetables"
    },

    {
        id: 3,
        name: "Classic Burger",
        category: "Burger",
        price: 159,
        emoji: "🍔",
        description: "Crispy patty with fresh vegetables"
    },

    {
        id: 4,
        name: "Cheese Burger",
        category: "Burger",
        price: 189,
        emoji: "🍔",
        description: "Double cheese & special sauce"
    },

    {
        id: 5,
        name: "Chicken Biryani",
        category: "Indian",
        price: 220,
        emoji: "🍛",
        description: "Aromatic rice with tender chicken"
    },

    {
        id: 6,
        name: "Paneer Biryani",
        category: "Indian",
        price: 190,
        emoji: "🍛",
        description: "Spiced basmati rice & paneer"
    },

    {
        id: 7,
        name: "Hakka Noodles",
        category: "Noodles",
        price: 179,
        emoji: "🍜",
        description: "Classic Indo-Chinese noodles"
    },

    {
        id: 8,
        name: "Schezwan Noodles",
        category: "Noodles",
        price: 199,
        emoji: "🍜",
        description: "Spicy noodles with vegetables"
    },

    {
        id: 9,
        name: "Chocolate Cake",
        category: "Dessert",
        price: 149,
        emoji: "🍰",
        description: "Rich chocolate cake"
    },

    {
        id: 10,
        name: "Ice Cream",
        category: "Dessert",
        price: 99,
        emoji: "🍨",
        description: "Creamy vanilla ice cream"
    }
];


let cart = [];
let orders = [];
let selectedCategory = "all";


/* DISPLAY FOOD */

function displayFood(list = foods) {

    const grid = document.getElementById("foodGrid");

    grid.innerHTML = "";

    if (list.length === 0) {

        grid.innerHTML = `
            <p style="grid-column:1/-1;text-align:center;padding:40px">
                No food found 😔
            </p>
        `;

        return;
    }

    list.forEach(food => {

        grid.innerHTML += `

        <div class="food-card">

            <div class="food-image">
                ${food.emoji}
            </div>

            <div class="food-info">

                <h3>${food.name}</h3>

                <p>${food.description}</p>

                <div class="food-bottom">

                    <span class="price">
                        ₹${food.price}
                    </span>

                    <button
                        class="add-btn"
                        onclick="addToCart(${food.id})">
                        +
                    </button>

                </div>

            </div>

        </div>
        `;
    });
}


/* FILTER */

function filterFood(category, button) {

    selectedCategory = category;

    document.querySelectorAll(".category")
        .forEach(btn => btn.classList.remove("active"));

    button.classList.add("active");

    if (category === "all") {

        displayFood(foods);

    } else {

        displayFood(
            foods.filter(food =>
                food.category === category
            )
        );
    }
}


/* SEARCH */

function searchFood() {

    const query =
        document.getElementById("searchBox")
        .value
        .toLowerCase();

    let result = foods.filter(food => {

        const matchesSearch =
            food.name.toLowerCase().includes(query);

        const matchesCategory =
            selectedCategory === "all" ||
            food.category === selectedCategory;

        return matchesSearch && matchesCategory;
    });

    displayFood(result);
}


/* ADD TO CART */

function addToCart(id) {

    const food = foods.find(item => item.id === id);

    cart.push(food);

    updateCartCount();

    showNotification(`${food.name} added to cart 🛒`);
}


/* CART COUNT */

function updateCartCount() {

    document.getElementById("cartCount")
        .textContent = cart.length;
}


/* OPEN CART */

function openCart() {

    const modal =
        document.getElementById("cartModal");

    modal.style.display = "flex";

    displayCart();
}


/* CLOSE CART */

function closeCart() {

    document.getElementById("cartModal")
        .style.display = "none";
}


/* DISPLAY CART */

function displayCart() {

    const container =
        document.getElementById("cartItems");

    container.innerHTML = "";

    if (cart.length === 0) {

        container.innerHTML =
            "<p>Your cart is empty 🍽️</p>";

        document.getElementById("cartTotal")
            .textContent = "0";

        return;
    }


    let total = 0;

    cart.forEach((food, index) => {

        total += food.price;

        container.innerHTML += `

        <div class="cart-item">

            <span>
                ${food.emoji} ${food.name}
            </span>

            <strong>
                ₹${food.price}
                <button
                    onclick="removeFromCart(${index})"
                    style="
                    border:none;
                    background:none;
                    color:red;
                    cursor:pointer;">
                    ×
                </button>
            </strong>

        </div>
        `;
    });

    document.getElementById("cartTotal")
        .textContent = total;
}


/* REMOVE */

function removeFromCart(index) {

    cart.splice(index, 1);

    updateCartCount();

    displayCart();
}


/* PLACE ORDER */

function placeOrder() {

    if (cart.length === 0) {

        alert("Your cart is empty!");

        return;
    }


    const priority =
        document.getElementById("priorityOrder")
        .checked;


    const order = {

        id:
            Math.floor(Math.random() * 9000) + 1000,

        items: [...cart],

        total:
            cart.reduce(
                (sum, food) =>
                    sum + food.price,
                0
            ),

        priority: priority,

        status: "Preparing",

        time: new Date().toLocaleTimeString()
    };


    orders.unshift(order);

    cart = [];

    updateCartCount();

    document.getElementById("priorityOrder")
        .checked = false;

    closeCart();

    displayOrders();

    showNotification(
        `Order #${order.id} placed successfully! 🎉`
    );

    document
        .getElementById("orders")
        .scrollIntoView();
}


/* DISPLAY ORDERS */

function displayOrders() {

    const container =
        document.getElementById("ordersContainer");

    if (orders.length === 0) {

        container.innerHTML = `
            <div class="empty-orders">
                <div>📦</div>
                <h3>No orders yet</h3>
                <p>Your placed orders will appear here.</p>
            </div>
        `;

        return;
    }


    container.innerHTML = "";


    orders.forEach(order => {

        const items =
            order.items
                .map(item => item.name)
                .join(", ");


        container.innerHTML += `

        <div class="order-card">

            <div class="order-info">

                <h3>
                    Order #${order.id}
                    ${order.priority ? "⚡" : ""}
                </h3>

                <p>${items}</p>

                <p>
                    ₹${order.total} • ${order.time}
                </p>

            </div>

            <div>

                <span class="status
                    ${order.priority ? "priority" : ""}">
                    ${order.priority
                        ? "Priority"
                        : order.status}
                </span>

            </div>

        </div>
        `;
    });
}


/* NOTIFICATION */

function showNotification(message) {

    const notification =
        document.createElement("div");

    notification.textContent = message;

    notification.style.position = "fixed";
    notification.style.bottom = "25px";
    notification.style.right = "25px";
    notification.style.background = "#241b18";
    notification.style.color = "white";
    notification.style.padding = "15px 22px";
    notification.style.borderRadius = "12px";
    notification.style.zIndex = "999";

    document.body.appendChild(notification);


    setTimeout(() => {

        notification.remove();

    }, 2500);
}


/* SCROLL */

function scrollToMenu() {

    document
        .getElementById("menu")
        .scrollIntoView();
}


/* INITIALIZE */

displayFood();
displayOrders();