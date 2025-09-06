// frontend/src/api/fetchData.js
export async function getPopular() {
    const res = await fetch("http://localhost:8080/api/popular");
    return res.json();
}
export async function getTopRated() {
    const res = await fetch("http://localhost:8080/api/top_rated");
    return res.json();
}
export async function getPosterPathBase(){
    return "https://image.tmdb.org/t/p/original";
}
