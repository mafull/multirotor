import express  from "express";

import comms    from "../comms";


const router = express.Router();


router.get("/stats", (req, res) => {
    res.json(comms.stats);
});

router.get("/messages", (req, res) => {
    res.json(comms.getLogMessages(""));
});

router.get("/messages/:sender", (req, res) => {
    res.json(comms.getLogMessages(req.params.sender));
});


export default router;
