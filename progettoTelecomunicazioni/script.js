const menuIcon = document.querySelector('.menu-icon');
const navbar = document.querySelector('.navbar');

// Funzione per gestire l'apertura e la chiusura della navbar quando si clicca sull'icona del menu
menuIcon.addEventListener('click', () => {
    navbar.classList.toggle('active');
    menuIcon.classList.toggle('active');
});

// Funzione per nascondere l'icona del menu quando la larghezza dello schermo è superiore a 768px
window.addEventListener('resize', () => {
    if (window.innerWidth > 768) {
        menuIcon.style.display = 'none';
        navbar.classList.remove('active');
    } else {
        menuIcon.style.display = 'flex';
    }
});


// Funzione per chiudere la navbar quando si clicca fuori dalla navbar stessa o sull'icona del menu
document.addEventListener('click', (event) => {
    const target = event.target;
    if (!target.closest('.header')) {
        navbar.classList.remove('active');
        menuIcon.classList.remove('active');
    }
});


function openInstagramPage() {
    // Reindirizziamo l'utente alla pagina Instagram desiderata
    href = "https://www.instagram.com/_edoardosecchiero_/";
}


let slides = document.querySelectorAll('.slide-container');
let index = 0;


function next() {
    slides[index].classList.remove('active');
    index = (index + 1) % slides.length;
    slides[index].classList.add('active');
}

function prev() {
    slides[index].classList.remove('active');
    index = (index - 1 + slides.length) % slides.length;
    slides[index].classList.add('active');
}

document.getElementById('next').onclick = next;
document.getElementById('prev').onclick = prev;

showSlide(index);
