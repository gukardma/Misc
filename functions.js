function toggleLoginModal(){
    const modal = document.getElementById("login-modal");
    if(getComputedStyle(modal).display == 'flex'){
        modal.style.display="none";
    }
}