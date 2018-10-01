import express from "express";

import loggerRoutes from "./logger";


const router = express.Router();


router.use("/logger", loggerRoutes);


export default router;
