const Log = require('../../models/Log')
const Plant = require('../../models/Plant')
const { auth, verifyRole, ROLES } = require('../auth')
const router = require('express').Router()

router.post('/', auth, async (req, res) => {
    if(res.locals._ent != 'plant') return res.sendStatus(422)
    const plant_id = res.locals._id
    try {
        const log = new Log(req.body);
        const doc = await log.save()
        await Plant.findByIdAndUpdate(plant_id, {
            $addToSet: {
                logs: doc._id
            }
        })
    } catch (e) {
        console.log(e)
        return res.sendStatus(500)
    }
    return res.sendStatus(200);
})


router.get('/', auth, async (req, res) => {
    if(!req.query.plant_id){
        return res.sendStatus(422)
    }
    const plant_id = req.query.plant_id
    try {
        const doc = await Plant.findById(plant_id)
            .populate({
                path: 'logs',
                select: '-_id -__v',
                options: {
                    limit: 10,
                    sort: {date: -1}
                }
            })
            .select('logs')
        return res.status(200).json(doc.logs);
    } catch (e) {
        console.log(e)
        return res.sendStatus(500)
    }
})

module.exports = router